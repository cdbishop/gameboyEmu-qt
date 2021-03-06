#include "DebugWindow.hpp"

#include "Registers.hpp"

#include <QtUiTools/quiloader.h>
#include <QtCore/qfile.h>
#include <qboxlayout.h>
#include <qpushbutton.h>

#include "spdlog/spdlog.h"

#include <sstream>
#include <fstream>

template<typename T>
QString FormatValueHex(const T& value) {
  return QString("%1").arg(value, 0, 16);
}

DebugWindow::DebugWindow(QApplication* app, QWidget *parent)
  :QMainWindow(parent),
  _app(app)
{
  ui.setupUi(this);
  connect(ui.btn_Next, &QPushButton::clicked, this, &DebugWindow::onNextBtnClicked);
  connect(ui.btn_Run, &QPushButton::clicked, this, &DebugWindow::OnRunBtnClicked);
  connect(ui.btn_Pause, &QPushButton::clicked, this, &DebugWindow::OnPauseBtnClicked);

  connect(ui.lineEdit_BreakPCValue, &QLineEdit::editingFinished, this, &DebugWindow::OnPCBreakEditingFinnished);
  connect(ui.lineEdit_BreakRegVal, &QLineEdit::editingFinished, this, &DebugWindow::OnRegBreakEditingFinnished);
  connect(ui.btn_AddPCBreak, &QPushButton::clicked, this, &DebugWindow::OnPCBreakAdd);
  connect(ui.btn_AddRegBreak, &QPushButton::clicked, this, &DebugWindow::OnRegBreakAdd);
  connect(ui.tbl_Breaks, &QTableWidget::itemSelectionChanged, this, &DebugWindow::OnBreakSelected);
  connect(ui.btn_RemoveBreak, &QPushButton::clicked, this, &DebugWindow::OnBreakRemove);  

  connect(ui.lst_History, &QAbstractItemView::clicked, this, &DebugWindow::OnPreviousStateSelected);
  connect(ui.lst_rom, &QListWidget::doubleClicked, this, &DebugWindow::OnRomInstructionDoubleClicked);

  std::ofstream historyFile("history.txt", std::ios::out | std::ios::trunc);
}

void DebugWindow::SetStateNotifier(std::shared_ptr<CpuStateNotifierQt> notifier) {
  bool ret = connect(notifier.get(), &CpuStateNotifierQt::NotifyStateSignal, this, &DebugWindow::OnNotifyStateSignal);
  ret = connect(notifier.get(), &CpuStateNotifierQt::NotifyRomDataSignal, this, &DebugWindow::OnNotifyRomDataSignal);
}

void DebugWindow::UpdateState(const cpu::State& state, const cpu::StateHistory& history, const std::string& memory_dump)
{
  std::lock_guard lk(_stateMutex);
  SetState(state);
  //std::ofstream historyFile("history.txt", std::ios::out | std::ios::app);
  //assert(historyFile.is_open());
  for (auto i = _cpuHistory.size(); i < state._history.size(); ++i) {
  //if (state._history.size() > 0) {
    //int i = state._history.size() - 1;
    std::ostringstream ss;
    ss << "[" << std::hex << state._history[i].first << "] " << state._history[i].second;
    ui.lst_History->addItem(QString(ss.str().c_str()));

    ss.str("");
    ss.clear();

    ss << state._history[i].second << " - [a: " << state._a << " b: " << state._b << " c: "
      << state._c << " d: " << state._d << " e: " << state._e << " h: " << state._h << " l: " << state._l
      << " flag: " << state._flag << " pc: " << state._pc << " sp: " << state._sp;

    ss << std::endl;
    ss << memory_dump;
    ss << std::endl;

    //historyFile << ss.str() << std::endl;
  }
  //historyFile.close();

  // TODO: change 50 to be max items in circular buffer
  // should stay in sync, as items in buffer are overridden
  while (ui.lst_History->count() > 50) {
    auto item = ui.lst_History->takeItem(0);
    delete item;
  }

  _cpuHistory = history;

  int index = static_cast<int>(state._pc);  
  ui.lst_rom->setCurrentRow(_pcIndexLookup[index]);
}

void DebugWindow::UpdateRomData(const std::vector<Cpu::RomInstruction>& instructions) {
  for (auto& instruction : instructions) {
    std::stringstream ss;
    ss << "[" << std::hex << static_cast<int>(instruction.first) << "]:" << instruction.second;
    ui.lst_rom->addItem(QString(ss.str().c_str()));
    QVariant data(instruction.first);
    ui.lst_rom->item(ui.lst_rom->count() - 1)->setData(Qt::UserRole, data);
    _pcIndexLookup[instruction.first] = (ui.lst_rom->count() - 1);
  }
}

void DebugWindow::SetState(const cpu::State& state) {
  ui.lineEditRegA->setText(FormatValueHex(state._a));
  ui.lineEditRegB->setText(FormatValueHex(state._b));
  ui.lineEditRegC->setText(FormatValueHex(state._c));
  ui.lineEditRegD->setText(FormatValueHex(state._d));
  ui.lineEditRegE->setText(FormatValueHex(state._e));
  ui.lineEditRegFlag->setText(FormatValueHex(state._flag));
  ui.lineEditRegH->setText(FormatValueHex(state._h));
  ui.lineEditRegL->setText(FormatValueHex(state._l));
  ui.lineEditRegPC->setText(FormatValueHex(state._pc));
  ui.lineEditRegSP->setText(FormatValueHex(state._sp));

  ui.lineEditRegBC->setText(FormatValueHex(state.ReadRegister(Register16::BC)));
  ui.lineEditRegDE->setText(FormatValueHex(state.ReadRegister(Register16::DE)));
  ui.lineEditRegHL->setText(FormatValueHex(state.ReadRegister(Register16::HL)));

  ui.chk_flagCarry->setChecked((state.TestFlag(cpu::Flag::Carry)));
  ui.chk_flagHalfCarry->setChecked((state.TestFlag(cpu::Flag::HalfCarry)));
  ui.chk_flagSubOp->setChecked((state.TestFlag(cpu::Flag::SubOp)));
  ui.chk_flagZero->setChecked((state.TestFlag(cpu::Flag::Zero)));

  ui.lineEditTimerM->setText(FormatValueHex(state._clock._m));
  ui.lineEditTimerT->setText(FormatValueHex(state._clock._t));

  ui.lst_History->setEnabled(true);
  ui.lst_rom->setEnabled(true);
  ui.btn_Next->setEnabled(true);
  ui.btn_Run->setEnabled(true);
}

void DebugWindow::onNextBtnClicked()
{
  spdlog::get("console")->debug("Next clicked!");
  emit Next();
}

void DebugWindow::OnRunBtnClicked()
{
  spdlog::get("console")->debug("Run clicked!");
  QString runMode = ui.cmbo_RunSpeed->itemText(ui.cmbo_RunSpeed->currentIndex());
  emit Run((runMode == "Debug") ? RunSpeed::Stepping : RunSpeed::Full);

  ui.lst_History->setEnabled(false);
  ui.lst_rom->setEnabled(false);
  ui.btn_Next->setEnabled(false);
  ui.btn_Run->setEnabled(false);
}

void DebugWindow::OnPauseBtnClicked()
{
  spdlog::get("console")->debug("Pause clicked!");
  emit Pause();

  ui.lst_History->setEnabled(true);
  ui.lst_rom->setEnabled(true);
  ui.btn_Next->setEnabled(true);
  ui.btn_Run->setEnabled(true);
}

void DebugWindow::OnPCBreakEditingFinnished()
{
  if (ui.lineEdit_BreakPCValue->text().length() > 0) {
    ui.btn_AddPCBreak->setEnabled(true);
  }
  else {
    ui.btn_AddPCBreak->setEnabled(false);
  }
}

void DebugWindow::OnRegBreakEditingFinnished()
{
  if (ui.lineEdit_BreakRegVal->text().length() > 0) {
    ui.btn_AddRegBreak->setEnabled(true);
  }
  else {
    ui.btn_AddRegBreak->setEnabled(false);
  }
}

void DebugWindow::OnPCBreakAdd()
{
  QString txt = std::move(ui.lineEdit_BreakPCValue->text());
  bool ok = false;
  unsigned int targetPC = txt.toUInt(&ok, 16);
  if (ok) {
    spdlog::get("console")->debug("setting pc break point to {}", targetPC);
    emit SetPCBreak(targetPC);
  }
  else {
    spdlog::get("console")->debug("failed to parse input as hex: {}", txt.toStdString());
  }

  QVariant regV("PC");
  QTableWidgetItem* regItem = new QTableWidgetItem("PC");
  regItem->setData(Qt::UserRole, regV);

  QTableWidgetItem* regValue = new QTableWidgetItem(txt);
  regValue->setData(Qt::UserRole, regV);

  ui.tbl_Breaks->insertRow(ui.tbl_Breaks->rowCount());
  ui.tbl_Breaks->setItem(ui.tbl_Breaks->rowCount() - 1, 0, regItem);
  ui.tbl_Breaks->setItem(ui.tbl_Breaks->rowCount() - 1, 1, regValue);
}

void DebugWindow::OnRegBreakAdd()
{
  QString reg = ui.cmbo_BreakRegSelect->itemText(ui.cmbo_BreakRegSelect->currentIndex());
  QString value = std::move(ui.lineEdit_BreakRegVal->text());
  bool ok = false;
  unsigned int targetValue = value.toUInt(&ok, 16);
  if (ok) {
    spdlog::get("console")->debug("setting reg break point on {} to {}", reg.toStdString(), targetValue);
    emit SetRegBreak(reg.toStdString(), targetValue);
  }
  else {
    spdlog::get("console")->debug("failed to parse input as hex: {}", value.toStdString());
  }

  QVariant regV(reg);
  QTableWidgetItem* regItem = new QTableWidgetItem(reg);
  regItem->setData(Qt::UserRole, regV);

  QTableWidgetItem* regValue = new QTableWidgetItem(value);
  regValue->setData(Qt::UserRole, regV);

  ui.tbl_Breaks->insertRow(ui.tbl_Breaks->rowCount());
  ui.tbl_Breaks->setItem(ui.tbl_Breaks->rowCount() - 1, 0, regItem);
  ui.tbl_Breaks->setItem(ui.tbl_Breaks->rowCount() - 1, 1, regValue);
}

void DebugWindow::OnBreakSelected()
{
  auto item = ui.tbl_Breaks->currentItem();
  ui.btn_RemoveBreak->setEnabled(item != nullptr);
}

void DebugWindow::OnBreakRemove()
{
  auto item = ui.tbl_Breaks->currentItem();
  QVariant v = item->data(Qt::UserRole);

  ui.tbl_Breaks->removeRow(item->row());  

  emit RemoveRegBreak(v.toString().toStdString());
}

void DebugWindow::OnPreviousStateSelected(const QModelIndex& index) {
  spdlog::get("console")->debug("selected index: {}", index.row());

  auto history = _cpuHistory[index.row()];
  SetState(history.second);
}

void DebugWindow::OnRomInstructionDoubleClicked(const QModelIndex& index) {
  auto item = ui.lst_rom->currentItem();
  auto row = ui.lst_rom->row(item);

  if (_pcBreakpoints.count(row)) {
    _pcBreakpoints.erase(row);
    item->setTextColor(QColor(0, 0, 0));
    auto pc = item->data(Qt::UserRole).value<unsigned short>();
    emit RemovePCBreak();
  } else {
    _pcBreakpoints.insert(ui.lst_rom->row(item));
    item->setTextColor(QColor(255, 0, 0));
    auto pc = item->data(Qt::UserRole).value<unsigned short>();
    emit SetPCBreak(pc);
  }
}

void DebugWindow::OnNotifyStateSignal(const cpu::State& state, const cpu::StateHistory& history, const std::string& memory_dump) {
  UpdateState(state, history, memory_dump);
}

void DebugWindow::OnNotifyRomDataSignal(const std::vector<Cpu::RomInstruction>& instructions) {
  UpdateRomData(instructions);
}
