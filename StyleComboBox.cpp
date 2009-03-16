/*
 * StyleComboBox.cpp is part of Brewtarget, and is Copyright Philip G. Lee
 * (rocketman768@gmail.com), 2009.
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

#include "StyleComboBox.h"
#include <list>

StyleComboBox::StyleComboBox(QWidget* parent)
        : QComboBox(parent)
{
}

void StyleComboBox::startObservingDB()
{
   if( ! Database::isInitialized() )
      Database::initialize();

   dbObs = Database::getDatabase();
   addObserved(dbObs);

   std::list<Style*>::iterator it, end;

   end = dbObs->getStyleEnd();

   for( it = dbObs->getStyleBegin(); it != end; ++it )
      addStyle(*it);
   repopulateList();

   setCurrentIndex(-1);
}

void StyleComboBox::addStyle(Style* style)
{
   styleObs.push_back(style);
   addObserved(style);

   addItem( tr(style->getName().c_str()) );
}

void StyleComboBox::removeAllStyles()
{
   /*
   removeAllObserved(); // Don't want to observe anything.
   styleObs.clear(); // Delete internal list.
    */

   int i;
   for( i = 0; i < styleObs.size(); ++i )
      removeObserved(styleObs[i]);
   styleObs.clear(); // Clear the internal list.
   clear(); // Clear the combo box's visible list.
}

void StyleComboBox::notify(Observable *notifier)
{
   unsigned int i, size;

   // Notifier could be the database.
   if( notifier == dbObs )
   {
      removeAllStyles();
      std::list<Style*>::iterator it, end;

      end = dbObs->getStyleEnd();

      for( it = dbObs->getStyleBegin(); it != end; ++it )
         addStyle(*it);
      repopulateList();
   }
   else // Otherwise, we know that one of the styles changed.
   {
      size = styleObs.size();
      for( i = 0; i < size; ++i )
         if( notifier == styleObs[i] )
         {
            // Notice we assume 'i' is an index into both 'styleObs' and also
            // to the text list in this combo box...
            setItemText(i, tr(styleObs[i]->getName().c_str()));
         }
   }
}

void StyleComboBox::setIndexByStyleName(std::string name)
{
   int ndx;

   ndx = findText( tr(name.c_str()), Qt::MatchExactly );
   if( ndx == -1 )
      return;

   setCurrentIndex(ndx);
}

void StyleComboBox::repopulateList()
{
   unsigned int i, size;
   clear();

   size = styleObs.size();
   for( i = 0; i < size; ++i )
      addItem( tr(styleObs[i]->getName().c_str()) );
}

Style* StyleComboBox::getSelected()
{
   if( currentIndex() >= 0 )
      return styleObs[currentIndex()];
   else
      return 0;
}