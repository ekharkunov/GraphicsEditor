#ifndef UNDOCOMMAND_HPP
#define UNDOCOMMAND_HPP

#include <QUndoCommand>

class UndoCommand : public QUndoCommand
{
public:
    explicit UndoCommand(QString text = "", QUndoCommand *parent = 0);
    virtual ~UndoCommand();
    void redo();
    void undo();
};

#endif // UNDOCOMMAND_HPP
