// Copyright 2026 Nikita
#pragma once

#include <cmath>
#include <fstream> // Библиотека для чтения и записи из файла.
#include <iostream>
#include <limits>
#include <stdexcept> // Библиотека для исключений.
#include <string>
#include <vector>

const double EPSILON = 1e-9; // Малое значение для сравнения с нулём.

template <typename TKey, typename TValue>
class BaseTable // Базовый класс (абстрактный) для всех таблиц. Содержит чисто
                // виртуальные методы для таблиц. Виртуальные методы возвращают
                // количество произведённых операций при выполнении
                // соответствующего действия.
{
public:
  struct FindResult // Структура для удобного возвращения значения и количества
                    // операций при выполнении find().
  {
    TValue *value; // Равен nullptr, если запись не найдена.
    size_t operationsCount;

    FindResult() : value(nullptr), operationsCount(0) {}
  };

  virtual size_t
  insert(const TKey &key,
         const TValue &value) = 0; // Вставка записи в таблицу (ключ-значение).
  virtual FindResult
  find(const TKey &key) = 0; // Поиск записи по ключу. Возвращает указатель на
                             // значение записи и количество произведённых
                             // операций при выполнении поиска.
  virtual size_t remove(const TKey &key) = 0; // Удаление записи по ключу.

  virtual std::string
  getTableName() const = 0; // Метод для получения имени (типа) таблицы. Нужно
                            // для логирования.
  virtual void clear() = 0; // Метод для очистки таблицы от всех записей.
  virtual size_t
  size() const = 0; // Метод для получения количества записей в таблице.
};