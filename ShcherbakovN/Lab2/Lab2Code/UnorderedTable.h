#pragma once
#include "BaseTable.h"

template <typename TKey, typename TValue>
class UnorderedTable : public BaseTable<TKey, TValue> // Неупорядоченная таблица.
{
private:
	using FindResult = typename BaseTable<TKey, TValue>::FindResult; // Псевдоним для удобства использования структуры FindResult из базового класса. typename - явно указывает компилятору, что FindResult является типом.

	struct TTableRecord // Структура для удобного хранения пар ключ-значение.
	{
		TKey key;
		TValue value;
	};

	std::vector<TTableRecord> records; // Вектор для хранения записей таблицы.
public:
	UnorderedTable() {}

	~UnorderedTable() {}

	std::string getTableName() const override
	{
		return "UnorderedTable";
	}

	void clear() override
	{
		records.clear();
	}

	size_t size() const override
	{
		return records.size();
	}

	TValue& operator[](const size_t index) // Перегруженный оператор [] для удобного доступа к значению записи по индексу.
	{
		return records[index].value;
	}

	size_t insert(const TKey& key, const TValue& value) override
	{
		size_t opCount = 0; // Счётчик количества операций.

		opCount += 2; // Операция records.size() и присваивание (sizeTable = records.size()).
		size_t sizeTable = records.size(); // Текущий размер таблицы.

		opCount++; // Цикл for - size_t i = 0.
		for (size_t i = 0; i < sizeTable; ++i)
		{
			opCount++; // Цикл for (i < sizeTable).

			opCount += 2; // Операции сравнения ключей (records[i].key == key) и доступа к records[i].
			if (records[i].key == key)
			{
				opCount += 2; // Операция присваивания (records[i].value = value) и операция доступа к records[i].
				records[i].value = value; // Если ключ найден, то перезаписываем значение.
				return opCount;
			}

			opCount++; // Цикл for (++i).
		}
		opCount++; // Цикл for (i < sizeTable).

		opCount++; // Операция вставки новой записи в таблицу (records.push_back({ key, value })).
		records.push_back({ key, value }); // Иначе вставляем новую запись в таблицу.
		return opCount;
	}

	FindResult find(const TKey& key) override
	{
		size_t opCount = 0; // Счётчик количества операций.

		FindResult result; // Объект стурктуры для хранения результата поиска.

		opCount += 2; // Операция records.size() и присваивание (sizeTable = records.size()).
		size_t sizeTable = records.size(); // Текущий размер таблицы.

		opCount++; // Цикл for - size_t i = 0.
		for (size_t i = 0; i < sizeTable; ++i)
		{
			opCount++; // Цикл for (i < sizeTable).

			opCount += 2; // Операции сравнения ключей (records[i].key == key) и доступа к records[i].
			if (records[i].key == key)
			{
				opCount += 3; // Операции присваивания (result.value = &records[i].value), взятия адреса и доступа к records[i] (&records[i].value)
				result.value = &records[i].value; // Указатель на значение найденной записи.

				opCount++; // Операция присваивания (result.operationsCount = opCount).
				result.operationsCount = opCount; // Количество операций, произведённых при поиске записи.

				return result; // Возвращаем результат поиска.
			}

			opCount++; // Цикл for (++i).
		}
		opCount++; // Цикл for (i < sizeTable).

		opCount++; // Операция присваивания (result.operationsCount = opCount).
		result.operationsCount = opCount; // Количество операций, произведённых при поиске записи (Но запись не найдена).
		return result; // Возвращаем результат поиска (Запись не найдена, указатель на значение равен nullptr).
	}

	size_t remove(const TKey& key) override
	{
		size_t opCount = 0; // Счётчик количества операций.

		opCount += 2; // Операция records.size() и присваивание (sizeTable = records.size()).
		size_t sizeTable = records.size(); // Текущий размер таблицы.

		opCount++; // Цикл for - size_t i = 0.
		for (size_t i = 0; i < sizeTable; ++i)
		{
			opCount++; // Цикл for (i < sizeTable).

			opCount += 2; // Операции сравнения ключей (records[i].key == key) и доступа к records[i].
			if (records[i].key == key) // Если ключ найден, то удаляем запись.
			{
				opCount += 2; // Операции присваивания (records[i] = records[sizeTable - 1]) и два доступа (records[i], records[sizeTable - 1]).
				records[i] = records[sizeTable - 1]; // Копируем последнюю запись на место удаляемой.

				opCount++; // Операция удаления последней записи (records.pop_back()).
				records.pop_back(); // Удаляем последнюю запись из таблицы.

				return opCount;
			}

			opCount++; // Цикл for (++i).
		}
		opCount++; // Цикл for (i < sizeTable).

		return opCount;
	}
};