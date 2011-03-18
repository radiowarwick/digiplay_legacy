/*
 * ShowplanDelegate.h
 *
 *  Created on: 20 Feb 2011
 *      Author: cc
 */

#ifndef SHOWPLANDELEGATE_H_
#define SHOWPLANDELEGATE_H_

#include <QtGui/QStyledItemDelegate>
#include <QtGui/QWidget>

#include "dps/DpsShowItem.h"

Q_DECLARE_METATYPE(DpsShowItem)

class ShowplanDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    ShowplanDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent) {}
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const;
//    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
//                          const QModelIndex &index) const;
//    void setEditorData(QWidget *editor, const QModelIndex &index) const;
//    void setModelData(QWidget *editor, QAbstractItemModel *model,
//                      const QModelIndex &index) const;

private slots:
//    void commitAndCloseEditor();
};

#endif /* SHOWPLANDELEGATE_H_ */
