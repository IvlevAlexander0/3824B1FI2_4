// Copyright 2026 Nikita
#pragma once
#include "AVLTable.h"
#include "HashTable.h"
#include "UnorderedTable.h"

class LoggingOperations // Класс для логирования количества произведенных
                        // операций пользователем.
{
private:
  struct InputLogs // Структура данных, подаваемых логгеру на вход при записи
                   // логов.
  {
    std::string tableName; // Имя (тип) таблицы.
    std::string operationName; // Имя (тип) выполненной операции (метода).
    size_t operationsCount; // Число операций, затраченных на выполнение метода.
  };

  std::vector<InputLogs> logs; // Набор логов.

  // Общее число операций для каждого действия:
  size_t totalInsert;
  size_t totalFind;
  size_t totalRemove;

  // Общее число операций у каждого типа таблиц:
  size_t totalUnorderedOp;
  size_t totalAVLOp;
  size_t totalHashOp;

public:
  LoggingOperations() {
    totalInsert = 0;
    totalFind = 0;
    totalRemove = 0;

    totalUnorderedOp = 0;
    totalAVLOp = 0;
    totalHashOp = 0;
  }

  ~LoggingOperations() {}

  void add(const std::string &tableName_, const std::string &operationName_,
           size_t operationsCount) // Добавление лога в набор логов.
  {
    logs.push_back({tableName_, operationName_, operationsCount});

    // Обновляем счётчики:
    if (operationName_ == "insert") {
      totalInsert += operationsCount;
    }
    if (operationName_ == "find") {
      totalFind += operationsCount;
    }
    if (operationName_ == "remove") {
      totalRemove += operationsCount;
    }

    if (tableName_ == "UnorderedTable") {
      totalUnorderedOp += operationsCount;
    }
    if (tableName_ == "AVLTable") {
      totalAVLOp += operationsCount;
    }
    if (tableName_ == "HashTable") {
      totalHashOp += operationsCount;
    }
  }

  void
  writeToFile(const std::string &fileName) const // Сохранение логов в файл.
  {
    std::ofstream fout; // Создание потока для записи в файл.
    fout.open(fileName); // Открытие файла для записи с именем fileName. Если
                         // файл не существует - он создастся автоматически.

    if (fout.is_open()) // is_open() - проверяет, открылся ли файл.
    {
      size_t logs_size = logs.size(); // Длина вектора логов.
      for (size_t i = 0; i < logs_size; ++i) {
        fout << logs[i].tableName << " " << logs[i].operationName << " "
             << logs[i].operationsCount
             << std::endl; // Запись строк логов в файл.
      }

      // Вывод общего числа операций каждого действия:
      fout << std::endl
           << "+------------------+TOTAL ACTIONS+------------------+"
           << std::endl;
      fout << "Insert: " << totalInsert << std::endl;
      fout << "Find: " << totalFind << std::endl;
      fout << "Remove: " << totalRemove << std::endl;

      // Вывод общего числа операций у каждого типа таблиц:
      fout << std::endl
           << "+---------------+TOTAL FOR EACH TABLE+---------------+"
           << std::endl;
      fout << "Unordered: " << totalUnorderedOp << std::endl;
      fout << "AVL: " << totalAVLOp << std::endl;
      fout << "Hash: " << totalHashOp << std::endl;

      fout.close(); // Закрытие файла.
    } else {
      std::cerr << "The file did not open!"
                << std::endl; // Вывод сообщения об ошибке открытия файла.
    }
  }

  void print() const // Печать текущих логов в консоль.
  {
    size_t logs_size = logs.size(); // Длина вектора логов.
    for (size_t i = 0; i < logs_size; ++i) {
      std::cout << logs[i].tableName << " " << logs[i].operationName << " "
                << logs[i].operationsCount
                << "\n"; // Вывод строк логов в консоль.
    }
  }

  void clear() // Очистка текущих логов.
  {
    logs.clear();

    totalInsert = 0;
    totalFind = 0;
    totalRemove = 0;

    totalUnorderedOp = 0;
    totalAVLOp = 0;
    totalHashOp = 0;
  }
};

template <typename TKey, typename TValue>
class MainTable // Класс для работы сразу со всеми 3 типами таблиц.
{
private:
  using FindResult = typename BaseTable<TKey, TValue>::
      FindResult; // Псевдоним для удобства использования структуры FindResult
                  // из базового класса. typename - явно указывает компилятору,
                  // что FindResult является типом.

  UnorderedTable<TKey, TValue> unorderedTable;
  AVLTable<TKey, TValue> avlTable;
  HashTable<TKey, TValue> hashTable;

  LoggingOperations logger; // Логгер.

public:
  MainTable() {}

  ~MainTable() {}

  size_t
  insertALL(const TKey &key,
            const TValue &value) // Вставка записи сразу во все 3 типа таблиц.
  {
    size_t opCountUnordered = unorderedTable.insert(key, value);
    logger.add(unorderedTable.getTableName(), "insert", opCountUnordered);

    size_t opCountAVL = avlTable.insert(key, value);
    logger.add(avlTable.getTableName(), "insert", opCountAVL);

    size_t opCountHash = hashTable.insert(key, value);
    logger.add(hashTable.getTableName(), "insert", opCountHash);

    return opCountUnordered + opCountAVL +
           opCountHash; // Возвращаем количество затраченных операций в сумме.
  }

  FindResult
  findALL(const TKey &key) // Поиск записи по ключу сразу в 3 типах таблиц.
  {
    FindResult resulttUnordered = unorderedTable.find(key);
    logger.add(unorderedTable.getTableName(), "find",
               resulttUnordered.operationsCount);

    FindResult resultAVL = avlTable.find(key);
    logger.add(avlTable.getTableName(), "find", resultAVL.operationsCount);

    FindResult resultHash = hashTable.find(key);
    logger.add(hashTable.getTableName(), "find", resultHash.operationsCount);

    FindResult result; // Объект стурктуры для хранения результата поиска.

    result.operationsCount =
        resulttUnordered.operationsCount + resultAVL.operationsCount +
        resultHash.operationsCount; // Количество затраченных операций в сумме.

    // Получаем значение искомой записи по ключу:
    if (resulttUnordered.value != nullptr) {
      result.value = resulttUnordered.value;
    } else if (resultAVL.value != nullptr) {
      result.value = resultAVL.value;
    } else if (resultHash.value != nullptr) {
      result.value = resultHash.value;
    } else {
      result.value = nullptr;
    }

    return result; // Возвращаем результат поиска.
  }

  size_t
  removeALL(const TKey &key) // Удаление записи по ключу сразу в 3 типах таблиц.
  {
    size_t opCountUnordered = unorderedTable.remove(key);
    logger.add(unorderedTable.getTableName(), "remove", opCountUnordered);

    size_t opCountAVL = avlTable.remove(key);
    logger.add(avlTable.getTableName(), "remove", opCountAVL);

    size_t opCountHash = hashTable.remove(key);
    logger.add(hashTable.getTableName(), "remove", opCountHash);

    return opCountUnordered + opCountAVL +
           opCountHash; // Возвращаем количество затраченных операций в сумме.
  }

  bool is_emptyALL() const // Проверка на пустоту сразу всех таблиц.
  {
    return (unorderedTable.size() == 0 && avlTable.size() == 0 &&
            hashTable.size() == 0);
  }

  void saveLogs(const std::string &fileName) {
    logger.writeToFile(fileName); // Сохраняем логи в файл с именем fileName.
  }
};