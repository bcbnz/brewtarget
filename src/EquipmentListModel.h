/*
* EquipmentListModel.h is part of Brewtarget, and is Copyright Philip G. Lee
* (rocketman768@gmail.com), 2009-2011.
*
* Brewtarget is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.

* Brewtarget is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.

* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QAbstractListModel>
#include <QModelIndex>
#include <QList>
#include <QMetaProperty>
#include <QVariant>

// Forward declarations.
class Equipment;
class Recipe;

class EquipmentListModel : public QAbstractListModel
{
   Q_OBJECT
   
public:
   EquipmentListModel(QWidget* parent = 0);
   
   //! Reimplemented from QAbstractListModel.
   virtual int rowCount( QModelIndex const& parent = QModelIndex() ) const;
   //! Reimplemented from QAbstractListModel.
   virtual QVariant data( QModelIndex const& index, int role = Qt::DisplayRole ) const;
   //! Reimplemented from QAbstractListModel.
   virtual QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

   void observeRecipe(Recipe* rec);
   void addEquipment(Equipment* equipment);
   void addEquipments(QList<Equipment*> equips);
   void removeEquipment(Equipment* equipment);
   void removeAll();
   
   Equipment* at(int ndx);
   int indexOf(Equipment* e);
   
public slots:
   void dbChanged(QMetaProperty,QVariant);
   void recChanged(QMetaProperty,QVariant);
   void equipChanged(QMetaProperty,QVariant);
   
private:
   QList<Equipment*> equipments;
   Recipe* recipe;
   
   void repopulateList();
};