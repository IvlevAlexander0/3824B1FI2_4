#pragma once
#include "BaseTable.h"

template <typename TKey, typename TValue>
class HashTable
    : public BaseTable<TKey, TValue> // Хэш-таблица. TKey - std::string.
{
private:
  using FindResult = typename BaseTable<TKey, TValue>::
      FindResult; // Псевдоним для удобства использования структуры FindResult
                  // из базового класса. typename - явно указывает компилятору,
                  // что FindResult является типом.

  struct NodeHash // Узел для метода цепочек в хэш-таблице. Способ борьбы с
                  // коллизиями.
  {
    TKey key;
    TValue value;
    NodeHash *next; // Указатель на следующий узел в цепочке. Если nullptr -
                    // конец цепочки.

    NodeHash(const TKey &key_, const TValue &value_)
        : key(key_), value(value_), next(nullptr) {}
  };

  std::vector<NodeHash *>
      table_lists; // Вектор для хранения указателей на начало цепочек (списки)
                   // в каждой ячейке хэш-таблицы.
  size_t sizeTable;     // Количество цепочек в хэш-таблице. Размер хэш-таблицы.
  size_t elementsCount; // Количество узлов (записей) в хэш-таблице.
  double loadFactor; // Коэффициент заполненности хэш-таблицы. Указывает на
                     // потребность увеличения размера хэш-таблицы (rehash()).

  size_t hashFunction(const TKey &key_, size_t sizeTable_, size_t &opCount)
      const // Вспомогательный метод - хэш-функция. Вычисляет индекс ячейки
            // хэш-таблицы для данного ключа.
  {
    opCount++;            // Операция присваивания (hashValue = 0).
    size_t hashValue = 0; // Значение хэша.

    opCount++; // Операция присваивания (sizeStr = key_.length()).
    size_t sizeStr = key_.length(); // Размер строки (ключа).

    opCount++; // Цикл for - size_t i = 0.
    for (size_t i = 0; i < sizeStr; ++i) {
      opCount++; // Цикл for (i < sizeStr).

      opCount += 4; // 4 операции для вычисления hashValue (присваивание,
                    // умножение, сложение, доступ по индексу):
      hashValue =
          hashValue * 31 +
          (unsigned char)key_[i]; // Вычисляем хэш-значение для строки (ключа).
                                  // (unsigned char)key_[i] - преобразует символ
                                  // строки в положительное число.

      opCount++; // Цикл for (++i).
    }
    opCount++; // Цикл for (i < sizeStr).

    opCount++; // Операция остатка от деления (hashValue % sizeTable_).
    return hashValue %
           sizeTable_; // Возвращаем индекс нужной цепочки в хэш-таблице,
                       // которая соответствует данному ключу.
  }

  NodeHash *
  findNode(const TKey &key,
           size_t &opCount) const // Вспомогательный метод для поиска узла
                                  // (записи) в хэш-таблице по ключу.
  {
    opCount++; // Операция присваивания (index = ...).
    size_t index = hashFunction(
        key, sizeTable,
        opCount); // Вычисляем индекс записи (номер цепочки) в хэш-таблице.

    opCount += 2; // Операции присваивания и доступа по индексу:
    NodeHash *currentNode = table_lists[index]; // Получаем указатель на начало
                                                // цепочки с индексом index.

    opCount++; // Операция сравнения указателя (currentNode != nullptr).
    while (currentNode != nullptr) // Пока не дошли до конца цепочки.
    {
      opCount++; // Операция сравнения ключей (currentNode->key == key).
      if (currentNode->key == key) {
        return currentNode; // Если нашли запись по ключу - возвращаем указатель
                            // на запись (узел).
      }

      opCount++; // Операция присваивания (currentNode = currentNode->next).
      currentNode = currentNode->next; // Переход к следующему узлу цепочки.

      opCount++; // Операция сравнения указателя (currentNode != nullptr).
    }

    return nullptr; // Если не нашли запись по ключу - возвращаем nullptr.
  }

  void rehash(size_t &opCount) // Вспомогательный метод для увеличения размера
                               // хэш-функции.
  {
    opCount += 2; // Операции присваивания (newSizeTable = ...) и умножения
                  // (sizeTable * 2).
    size_t newSizeTable =
        sizeTable * 2; // Удваиваем количество цепочек хэш-таблицы.

    std::vector<NodeHash *> new_table_lists(
        newSizeTable,
        nullptr); // Создаём новую хэш-таблицу с размером (количеством цепочек)
                  // newSizeTable и инициклизируем цепочки nullptr.

    opCount++; // Цикл for - size_t i = 0.
    for (size_t i = 0; i < sizeTable;
         ++i) // Проход по всем цепочкам старой хэш-таблицы.
    {
      opCount++; // Цикл for (i < sizeTable).

      opCount += 2; // Операции присваивания и доступа по индексу:
      NodeHash *currentNode = table_lists[i]; // Указатель на начало i-ой
                                              // цепочки в старой хэш-таблице.

      opCount++; // Операция сравнения указателя (currentNode != nullptr).
      while (currentNode != nullptr) // Пока не дошли до конца цепочки.
      {
        opCount++; // Операция присваивания (currentNextNode =
                   // currentNode->next).
        NodeHash *currentNextNode =
            currentNode->next; // Сохраняем указатель на следующий элемент
                               // цепочки в старой хэш-таблице.

        opCount++; // Операция присваивания (index = ...).
        size_t index =
            hashFunction(currentNode->key, newSizeTable,
                         opCount); // Получаем новый индекс для текущего узла в
                                   // новой хэш-таблице.

        // Вставка текущего элемента старой хэш-таблицы в начало цепочки новой
        // хэш-таблицы:
        opCount += 4; // По две операции присваивания и доступа по индексу:
        currentNode->next =
            new_table_lists[index]; // Присоединяем цепочку с индексом index
                                    // новой хэш-таблицы к текущему элементу
                                    // (справа).
        new_table_lists[index] =
            currentNode; // Копируем цепочку с индексом index (и текущим
                         // элементом currentNode спереди цепочки) в новую
                         // хэш-таблицу.

        opCount++; // Операция присваивания (currentNode = currentNextNode).
        currentNode = currentNextNode; // Переход к следующему узлу цепочки в
                                       // старой хэш-таблице.

        opCount++; // Операция сравнения указателя (currentNode != nullptr).
      }

      opCount++; // Цикл for (++i).
    }
    opCount++; // Цикл for (i < sizeTable).

    opCount += 2; // Две операции присваивания:
    table_lists =
        new_table_lists; // Копируем новую хэш-таблицу на место старой.
    sizeTable =
        newSizeTable; // Обновляем размер (количество цепочек) хэш-таблицы.
  }

public:
  HashTable(size_t sizeTable_ = 10, double loadFactor_ = 0.75) {
    if (loadFactor_ < 0 ||
        std::fabs(loadFactor_) < EPSILON) // std::fabs - абсолютное значение.
    {
      loadFactor_ = 0.75; // Значение по умолчанию.
    }
    loadFactor = loadFactor_;

    if (sizeTable_ == 0) {
      sizeTable_ = 10; // Значение по умолчанию.
    }
    sizeTable = sizeTable_;
    table_lists.resize(sizeTable,
                       nullptr); // Задаём размер вектора, содержащего цепочки.
                                 // Инициализируем каждый элемент nullptr.

    elementsCount = 0; // Обновляем количество узлов (записей) в хэш-таблице.
  }

  void clear() override {
    for (size_t i = 0; i < sizeTable;
         ++i) // Проход по всем цепочкам хэш-таблицы.
    {
      NodeHash *currentNode = table_lists[i]; // Указатель на начало i-ой
                                              // цепочки в старой хэш-таблице.

      while (currentNode != nullptr) // Пока не дошли до конца цепочки.
      {
        NodeHash *currentNextNode =
            currentNode->next; // Сохраняем указатель на следующий узел цепочки
                               // хэш-таблицы.
        delete currentNode;            // Удаляем текущий узел хэш-таблицы.
        currentNode = currentNextNode; // Переход к следующему узлу цепочки.
      }

      table_lists[i] = nullptr; // Обновляем указатель на начало i-ой цепочки.
    }

    elementsCount = 0; // Обновляем количество узлов (записей) в хэш-таблице.
  }

  ~HashTable() { clear(); }

  std::string getTableName() const override { return "HashTable"; }

  size_t size() const override { return elementsCount; }

  size_t size_capacity() const // Метод для тестирования. Выводит размер вектора
                               // цепочек table_lists (количество цепочек).
  {
    return sizeTable;
  }

  size_t insert(const TKey &key, const TValue &value) override {
    size_t opCount = 0; // Счётчик количества операций.

    opCount++; // Операция присваивания (size_t index = ...).
    size_t index = hashFunction(key, sizeTable,
                                opCount); // Получаем индекс нужной цепочки для
                                          // данной записи в хэш-таблице.
    opCount += 2; // Операции присваивания и доступа по индексу:
    NodeHash *currentNode = table_lists[index]; // Получаем указатель на начало
                                                // цепочки с индексом index.

    opCount++; // Операция сравнения указателя (currentNode != nullptr).
    while (currentNode != nullptr) // Пока не дошли до конца цепочки.
    {
      opCount++; // Операция сравнения ключей (currentNode->key == key).
      if (currentNode->key == key) {
        opCount++; // Операция присваивания (currentNode->value = value).
        currentNode->value =
            value; // Если нашли запись по ключу, то перезаписываем значение.
        return opCount;
      }

      opCount++; // Операция присваивания (currentNode = currentNode->next).
      currentNode = currentNode->next; // Переход к следующему узлу цепочки.

      opCount++; // Операция сравнения указателя (currentNode != nullptr).
    }

    opCount += 2; // Операции присваивания и new:
    NodeHash *resultNode = new NodeHash(
        key,
        value); // Создаём новую запись (если не нашли запись с ключом key).

    // Вставка новой записи в начало цепочки с индексом index:
    opCount += 4; // По две операции присваивания и доступа по индексу:
    resultNode->next =
        table_lists[index]; // Присоединяем цепочку с индексом index справа к
                            // реульзирующей записи.
    table_lists[index] =
        resultNode; // Присоединяем цепочку с индексом index и новой записью в
                    // начале цепочки к хэш-таблице.

    opCount++;       // Операция инкремента (elementsCount++).
    elementsCount++; // Обновляем количество узлов (записей) в хэш-таблице.

    opCount += 2; // Операции сравнения (>) и умножения:
    if ((double)elementsCount >
        loadFactor * (double)sizeTable) // Проверка на заполненность
                                        // хэш-таблицы: (double)elementsCount /
                                        // (double)sizeTable > loadFactor.
    {
      rehash(opCount); // Увеличиваем размер хэш-таблицы.
    }

    return opCount;
  }

  FindResult find(const TKey &key) override {
    size_t opCount = 0; // Счётчик количества операций.

    FindResult result; // Объект стурктуры для хранения результата поиска.

    opCount++; // Операция присваивания (resultNode = ...).
    NodeHash *resultNode = findNode(key, opCount);

    opCount++; // Операция сравнения указателя (resultNode != nullptr).
    if (resultNode != nullptr) // Если запись найдена.
    {
      opCount +=
          2; // Операции присваивания (result.value = ...) и взятия адреса (&).
      result.value = &(resultNode->value); // Указатель на значение найденной
                                           // записи (resultNode->value).

      opCount++; // Операция присваивания (result.operationsCount = opCount).
      result.operationsCount =
          opCount; // Количество операций, произведённых при поиске записи.

      return result; // Возвращаем результат поиска.
    }

    opCount++; // Операция присваивания (result.operationsCount = opCount).
    result.operationsCount = opCount; // Количество операций, произведённых при
                                      // поиске записи (Но запись не наёдена).

    return result; // Возвращаем результат поиска (Запись не найдена, указатель
                   // на значение равен nullptr).
  }

  size_t remove(const TKey &key) override {
    size_t opCount = 0; // Счётчик количества операций.

    opCount++; // Операция присваивания (index = ).
    size_t index = hashFunction(key, sizeTable,
                                opCount); // Получаем индекс нужной цепочки для
                                          // данной записи в хэш-таблице.

    opCount += 3; // Две операции присваиавния и операция доступа по индексу:
    NodeHash *currentNode =
        table_lists[index]; // Указатель на начало нужной цепочки.
    NodeHash *previousNode =
        nullptr; // Указатель на предыдущую запись (узел) в цепочке.

    opCount++; // Операция сравнения указателя (currentNode != nullptr).
    while (currentNode != nullptr) // Проход по всем записям (узлам) цепочки.
    {
      opCount++; // Операция сравнения ключей (currentNode->key == key).
      if (currentNode->key == key) // Если нашли нужную запись.
      {
        opCount++; // Операция сравнения указателя (previousNode == nullptr).
        if (previousNode == nullptr) {
          opCount += 2; // Операции доступа по индексу и присваивания:
          table_lists[index] =
              currentNode->next; // Если нужная запись - в начале цепочки, то
                                 // меняем указатель на начало цепочки.
        } else {
          opCount++; // Операции присваивания:
          previousNode->next =
              currentNode->next; // Если нужная запись - не в начале цепочки, то
                                 // соединяем указатель на предыдущий элемент с
                                 // указателем на следующий элемент.
        }

        opCount++;          // Операция удаления узла (delete).
        delete currentNode; // Удаляем текущую запись (узел).
        opCount++;          // Операция декремента (elementsCount--).
        elementsCount--; // Обновляем количество узлов (записей) в хэш-таблице.

        return opCount;
      }

      opCount += 2; // Две операции присваивания:
      previousNode =
          currentNode; // Обновляем указатель на предыдущую запись (узел).
      currentNode =
          currentNode->next; // Переход к следующей записи (узлу) в цепочке.

      opCount++; // Операция сравнения указателя (currentNode != nullptr).
    }

    return opCount;
  }
};