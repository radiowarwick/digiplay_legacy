/*
 * ShowplanDelegate.cpp
 *
 *  Created on: 20 Feb 2011
 *      Author: cc
 */

#include <iostream>
using namespace std;

#include <QtGui/QPainter>

#include "ShowplanDelegate.h"

void ShowplanDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
    if (qVariantCanConvert<DpsShowItem>(index.data())) {
        DpsShowItem vItem = qVariantValue<DpsShowItem>(index.data());
        QString vItemTitle  = QString::fromStdString(vItem.getName());
        QString vItemLength = QString::fromStdString(vItem.getLength().getHms());
        int vRectLeft = option.rect.left();
        int vRectRight = option.rect.right();
        int vRectTop = option.rect.top();
        int vRectBottom = option.rect.bottom();

        // Draw background
        QLinearGradient vGrad(0, vRectBottom, 0, vRectTop);
        QImage vIcon;
        if (option.state & QStyle::State_Selected) {
            vGrad.setColorAt(0.1, QColor(0,193,209));
            vGrad.setColorAt(0.9, QColor(0,213,229));
            vIcon = QImage(":/icons/music32.png");
        }
        else {
            vGrad.setColorAt(0.1, QColor(0,133,149));
            vGrad.setColorAt(0.9, QColor(0,153,169));
            vIcon = QImage(":/icons/music32.png");
        }
        painter->fillRect(option.rect, vGrad);

        // Add title
        QFont vFontTitle;
        vFontTitle.setPointSize(11);
        vFontTitle.setBold(true);
        painter->setFont(vFontTitle);
        painter->drawText(42, vRectTop + 20, vItemTitle);

        // Add length
        QFont vFontLength;
        vFontLength.setPointSize(9);
        vFontTitle.setBold(true);
        painter->setFont(vFontLength);
        QFontMetrics vFontMetric = painter->fontMetrics();
        painter->drawText(vRectRight - vFontMetric.width(vItemLength) - 10,
                          vRectTop + 40, vItemLength);

        // Add Icon
        painter->drawImage(QRect(vRectLeft + 5, vRectTop + 5, 32, 32), vIcon);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QSize ShowplanDelegate::sizeHint(const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    if (qVariantCanConvert<DpsShowItem>(index.data())) {
        DpsShowItem item = qVariantValue<DpsShowItem>(index.data());
        return QSize(0,50);
    } else {
        return QStyledItemDelegate::sizeHint(option, index);
    }
}
