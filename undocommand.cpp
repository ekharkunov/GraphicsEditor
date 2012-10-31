#include "undocommand.hpp"

UndoCommand::UndoCommand(QString text, QUndoCommand *parent) :
    QUndoCommand(text, parent)
{
}

UndoCommand::~UndoCommand()
{
}

void UndoCommand::redo()
{
}

void UndoCommand::undo()
{
}
