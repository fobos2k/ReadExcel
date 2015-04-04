#include <iostream>
#include <cstdlib>
#include <cstring>

#include "libxl.h"
using namespace libxl;

int main(int argc, char * argv[])
{
  std::clog << "Тестирование чтения маршрутов из XLS" << std::endl;
  std::clog << "------------------------------------" << std::endl;
  std::clog << std::endl;

  // Проверим был ли передан файл с маршрутами
  if ( argc < 2 ) {
    std::clog << "ОШИБКА! Необходимо передать в качестве параметра XLS-файл с маршрутами!" << std::endl;
    exit(1);
  }

  // Количество строк в заголовке
  const int nHeaderRows = 8;

  // Имя файла
  char * sFileName = argv[1];
  Book * pWB = xlCreateBook();
  if ( pWB ) {
    if ( pWB-> load(sFileName) ) {
      std::clog << "Обрабатываем файл " << sFileName << "..." << std::endl;
      int nCount = pWB->sheetCount();
      std::clog << "В книге " << nCount << " листов." << std::endl;
      
      // Работаем с листом
      Sheet * pWS = pWB->getSheet(0);
      if ( pWS ) {
	int nRowsCount = pWS->lastRow();
	std::clog << "На листе " << nRowsCount << " строк с данными." << std::endl;
	std::clog << "|   №   | Дата поездки |" << std::endl;
	std::clog << "+-------+--------------+" << std::endl;

	int iTrip = 1;
	for ( int i = nHeaderRows + 1; i < nRowsCount; i++ ) {
	  if ( pWS->isDate(i, 3) ) { // Если есть дата в третьей колонке
	    std::clog << iTrip; // Номер по порядку выбранного маршрута
	    iTrip++;

	    double fDateValue = pWS->readNum(i, 3);
	    int iYear, iMonth, iDay;
	    if ( pWB->dateUnpack(fDateValue, &iYear, &iMonth, &iDay) ) {
	      std::clog << "  " << iDay << "-" << iMonth << "-" << iYear;
	    }
	    
	    std::clog << std::endl;
	  }
	  else {
	    std::clog << pWB->errorMessage() << std::endl;
	  }

	}
      }
    }
    
    pWB->release();
    return EXIT_SUCCESS;
  }

  return EXIT_FAILURE;
}
