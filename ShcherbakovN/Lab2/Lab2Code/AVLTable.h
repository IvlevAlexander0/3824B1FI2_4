#pragma once
#include "BaseTable.h"

template <typename TKey, typename TValue>
class AVLTable
    : public BaseTable<TKey,
                       TValue> // Упорядоченная таблица на сбалансированном
                               // бинарном дереве поиска (АВЛ-дерево).
{
private:
  using FindResult = typename BaseTable<TKey, TValue>::
      FindResult; // Псевдоним для удобства использования структуры FindResult
                  // из базового класса. typename - явно указывает компилятору,
                  // что FindResult является типом.

  struct Node // Узел АВЛ-дерева.
  {
    TKey key;
    TValue value;

    Node *left;  // Указатель на левого потомка.
    Node *right; // Указатель на правого потомка.

    int height; // Высота текущего узла (поддерева). Максимальная длина пути от
                // данного узла до самого глубокого листа. Высота листа равна 1,
                // высота пустого дерева равна 0.

    Node(const TKey &key_, const TValue &value_)
        : key(key_), value(value_), left(nullptr), right(nullptr), height(1) {}
  };

  Node *root; // Указатель на корень АВЛ-дерева.
  size_t NodeCount; // Количество узлов (записей) в АВЛ-дереве.

  int getHeight(Node *node_, size_t &opCount)
      const // Вспомогательный метод получения высоты узла.
  {
    opCount += 2; // Операции сравнения (node_ != nullptr) и тернарный оператор.
    return (node_ != nullptr) ? (node_->height) : 0;
  }

  int getBalanceIndicator(Node *node_, size_t &opCount)
      const // Вспомогательный метод получения показателя баланса узла
            // АВЛ-дерева: разность высот правого и левого поддеревьев.
  {
    opCount++; // Сравнение указателя (node_ == nullptr).
    if (node_ == nullptr) {
      return 0; // Если узел равен nullptr, то его баланс считается 0, так как
                // он не имеет потомков.
    }

    opCount++; // Операция вычитания:
    return (getHeight(node_->right, opCount) -
            getHeight(node_->left,
                      opCount)); // Считаем показатель баланса для данного узла.
  }

  void
  updatedHeight(Node *node_,
                size_t &opCount) // Вспомогательный метод для обновления высоты
                                 // узла после операций вставки или удаления.
  {
    opCount++; // Сравнение указателя (node_ != nullptr).
    if (node_ != nullptr) {
      opCount++;   // Операция присваивания (max = 0).
      int max = 0; // Максимальная высота среди правого и левого поддерева.

      opCount++; // Операция сравнения (>=).
      if (getHeight(node_->left, opCount) >= getHeight(node_->right, opCount)) {
        opCount++; // Операция присваивания (max = ...).
        max = getHeight(node_->left, opCount);
      } else {
        opCount++; // Операция присваивания (max = ...).
        max = getHeight(node_->right, opCount);
      }

      opCount += 2; // Операции присваивания (node_->height = ...) и сложения (1
                    // + max).
      node_->height = 1 + max; // Высота узла = 1 + максимальная высота его
                               // левого и правого поддеревьев.
    }
  }

  Node *smallLeftRotation(
      Node *node_,
      size_t &opCount) // Вспомогательный метод для выполнения малого левого
                       // вращения (LL). Когда показатель баланса текущего узла
                       // (node_) больше или равен +2 и показатель баланса его
                       // правого потомка (rightNode) больше или равен 0.
  {
    opCount += 3; // Операции сравнения:
    if (node_ == nullptr ||
        node_->right ==
            nullptr) // Если текущий узел (node_) равен nullptr или его правый
                     // потомок (node_->right) равен nullptr, то малое левое
                     // вращение (LL) невозможно выполнить. В этом случае
                     // возвращаем текущий узел (node_) без изменений.
    {
      return node_;
    }

    opCount += 2; // Операции присваивания:
    Node *rightNode =
        node_->right; // Указатель на правого потомка текущего узла (node_).
    Node *leftSubTreeOfRightNode =
        rightNode->left; // Указатель на левое поддерево правого потомка
                         // текущего узла (node_).

    opCount += 2;            // Операции присваивания:
    rightNode->left = node_; // Делаем правого потомка (rightNode) новым корнем
                             // поддерева, а текущий узел (node_) становится
                             // левым потомком нового корня (rightNode).
    node_->right =
        leftSubTreeOfRightNode; // Левое поддерево правого потомка
                                // (leftSubTreeOfRightNode) становится правым
                                // потомком текущего узла (node_).

    // Обновляем высоты узлов после вращения.
    updatedHeight(node_, opCount);
    updatedHeight(rightNode, opCount);

    return rightNode; // Возвращаем новый корень поддерева после вращения
                      // (rightNode).
  }

  Node *smallRightRotation(
      Node *node_,
      size_t &opCount) // Вспомогательный метод для выполнения малого правого
                       // вращения (RR). Когда показатель баланса текущего узла
                       // (node_) меньше или равен -2 и показатель баланса его
                       // левого потомка (leftNode) меньше или равен 0.
  {
    opCount += 3; // Операции сравнения:
    if (node_ == nullptr ||
        node_->left ==
            nullptr) // Если текущий узел (node_) равен nullptr или его левый
                     // потомок (node_->left) равен nullptr, то малое правое
                     // вращение (RR) невозможно выполнить. В этом случае
                     // возвращаем текущий узел (node_) без изменений.
    {
      return node_;
    }

    opCount += 2; // Операции присваивания:
    Node *leftNode =
        node_->left; // Указатель на левого потомка текущего узла (node_).
    Node *rightSubTreeOfLeftNode =
        leftNode->right; // Указатель на правое поддерево левого потомка
                         // текущего узла (node_).

    opCount += 2; // Операции присваивания:
    leftNode->right = node_; // Делаем левого потомка (leftNode) новым корнем
                             // поддерева, а текущий узел (node_) становится
                             // правым потомком нового корня (leftNode).
    node_->left =
        rightSubTreeOfLeftNode; // Правое поддерево левого потомка
                                // (rightSubTreeOfLeftNode) становится левым
                                // потомком текущего узла (node_).

    // Обновляем высоты узлов после вращения.
    updatedHeight(node_, opCount);
    updatedHeight(leftNode, opCount);

    return leftNode; // Возвращаем новый корень поддерева после вращения
                     // (leftNode).
  }

  Node *bigLeftRotation(
      Node *node_,
      size_t &opCount) // Вспомогательный метод для выполнения большого левого
                       // вращения (RL). Когда показатель баланса текущего узла
                       // (node_) больше или равен +2 и показатель баланса его
                       // правого потомка (rightNode) меньше или равен -1.
  {
    opCount++; // Операция присваивания (node_->right = ...).
    node_->right = smallRightRotation(
        node_->right,
        opCount); // Выполняем малое правое вращение (RR) на правом потомке
                  // текущего узла (node_->right), чтобы преобразовать ситуацию
                  // в случай малого левого вращения (LL).
    return smallLeftRotation(
        node_, opCount); // Выполняем малое левое вращение (LL) на текущем узле
                         // (node_), чтобы сбалансировать поддерево и вернуть
                         // новый корень после большого левого вращения (RL).
  }

  Node *bigRightRotation(
      Node *node_,
      size_t &opCount) // Вспомогательный метод для выполнения большого правого
                       // вращения (LR). Когда показатель баланса текущего узла
                       // (node_) меньше или равен -2 и показатель баланса его
                       // левого потомка (leftNode) больше или равен +1.
  {
    opCount++; // Операция присваивания (node_->left = ...).
    node_->left = smallLeftRotation(
        node_->left,
        opCount); // Выполняем малое левое вращение (LL) на левом потомке
                  // текущего узла (node_->left), чтобы преобразовать ситуацию в
                  // случай малого правого вращения (RR).
    return smallRightRotation(
        node_, opCount); // Выполняем малое правое вращение (RR) на текущем узле
                         // (node_), чтобы сбалансировать поддерево и вернуть
                         // новый корень после большого правого вращения (LR).
  }

  Node *balancingTree(
      Node *node_,
      size_t &opCount) // Вспомогательный метод для балансировки АВЛ-дерева
                       // после операций вставки или удаления.
  {
    opCount++; // Сравнение указателя (node_ == nullptr).
    if (node_ == nullptr) {
      return nullptr;
    }

    updatedHeight(node_,
                  opCount); // Сначала обновляем высоту текущего узла (node_).

    opCount += 3; // Операции присваивания:
    int balanceIndicatorNode = getBalanceIndicator(
        node_, opCount); // Получаем показатель баланса текущего узла (node_).
    int balanceIndicatorLeftNode = getBalanceIndicator(
        node_->left, opCount); // Получаем показатель баланса левого потомка
                               // текущего узла (node_->left).
    int balanceIndicatorRightNode = getBalanceIndicator(
        node_->right, opCount); // Получаем показатель баланса правого потомка
                                // текущего узла (node_->right).

    // Левые вращения (LL и RL).
    opCount++; // Операция сравнения (balanceIndicatorNode >= 2).
    if (balanceIndicatorNode >= 2) {
      opCount++; // Операция сравнения (balanceIndicatorRightNode >= 0).
      if (balanceIndicatorRightNode >= 0) {
        return smallLeftRotation(
            node_, opCount); // Случай малого левого вращения (LL).
      } else if (balanceIndicatorRightNode <= -1) {
        opCount++; // Операция сравнения (balanceIndicatorRightNode <= -1).
        return bigLeftRotation(
            node_, opCount); // Случай большого левого вращения (RL).
      }
    }

    // Правые вращения (RR и LR).
    opCount++; // Операция сравнения (balanceIndicatorNode <= -2).
    if (balanceIndicatorNode <= -2) {
      opCount++; // Операция сравнения (balanceIndicatorLeftNode <= 0).
      if (balanceIndicatorLeftNode <= 0) {
        return smallRightRotation(
            node_, opCount); // Случай малого правого вращения (RR).
      } else if (balanceIndicatorLeftNode >= 1) {
        opCount++; // Операция сравнения (balanceIndicatorLeftNode >= 1).
        return bigRightRotation(
            node_, opCount); // Случай большого правого вращения (LR).
      }
    }

    return node_; // Если балансировка не требуется, возвращаем текущий узел
                  // (node_).
  }

  Node *insertNode(
      Node *node_, const TKey &key, const TValue &value,
      size_t &opCount) // Вспомогательный метод для вставки узла (записи) в
                       // АВЛ-дерево. Рекурсивный метод. Возвращает указатель на
                       // корень поддерева после вставки и балансировки.
  {
    opCount++; // Сравнение указателя (node_ == nullptr).
    if (node_ == nullptr) // Если достигнут nullptr, то нашли место для вставки
                          // нового узла (записи) после листа.
    {
      opCount += 2; // Операции создания нового узла (new Node(key, value)) и
                    // инкремента (NodeCount++).
      NodeCount++; // Обновляем количество узлов (записей) в АВЛ-дереве.
      return new Node(key,
                      value); // Создаём новый узел (запись) и возвращаем его.
    }

    // Поиск места для вставки по ключу (рекурсивно).
    opCount++; // Операция сравнения ключей (key < node_->key).
    if (key < node_->key) {
      opCount++; // Операция присваивания указателя (node_->left = ...).
      node_->left =
          insertNode(node_->left, key, value,
                     opCount); // Рекурсивно проваливаемся в левое поддерево.
    } else if (key > node_->key) {
      opCount++; // Операция присваивания указателя (node_->right = ...).
      node_->right =
          insertNode(node_->right, key, value,
                     opCount); // Рекурсивно проваливаемся в правое поддерево.
    } else {
      opCount++; // Операция сравнения ключей (key > node_->key).

      opCount++; // Операция присваивания значения (node_->value = ...).
      node_->value = value; // Если найден узел (запись) с текущим ключом, то
                            // перезаписыаем значение.
      return node_; // Возвращаем текущий узел (node_).
    }
    opCount++; // Операция сравнения ключей (key > node_->key).

    return balancingTree(
        node_, opCount); // Запуск балансировки АВЛ-дерева после вставки нового
                         // узла (записи). Балансировка производится со всеми
                         // узлами, которые встретились на пути: от места
                         // вставки до корня (рекурсивно).
  }

  Node *
  findNode(Node *node_, const TKey &key,
           size_t &opCount) // Вспомогательный метод для поиска узла (записи) в
                            // АВЛ-дерево по ключу. Рекурсивный метод.
                            // Возвращает указатель на найденный узел (запись)
                            // или nullptr, если запись не найдена.
  {
    opCount++; // Сравнение указателя (node_ == nullptr).
    if (node_ == nullptr) // Если достигнут nullptr, то узел (запись) не наёден
                          // (так как прошли через лист).
    {
      return nullptr;
    }

    opCount++; // Операция сравнения ключей (node_->key == key).
    if (node_->key ==
        key) // Если найден узел (запись) с текущим ключом, то возвращаем его.
    {
      return node_;
    }

    opCount++; // Операция сравнения ключей (key < node_->key).
    if (key < node_->key) {
      return findNode(node_->left, key,
                      opCount); // Рекурсивно проваливаемся в левое поддерево.
    } else                      // (key > node_->key)
    {
      return findNode(node_->right, key,
                      opCount); // Рекурсивно проваливаемся в правое поддерево.
    }
  }

  Node *maxNode(Node *node_,
                size_t &opCount) // Вспомогательный метод для поиска узла
                                 // (записи) с максимальным ключом в поддереве,
                                 // корнем которого является node_.
  {
    opCount += 3; // Цикл while (node_ != nullptr, сравнение && и node_->right
                  // != nullptr).
    while (node_ != nullptr && node_->right != nullptr) {
      opCount++; // Операция присваивания указателей (node_ = node_->right).
      node_ = node_->right;

      opCount += 3; // Цикл while (node_ != nullptr, сравнение && и node_->right
                    // != nullptr).
    }
    return node_;
  }

  Node *
  removeNode(Node *node_, const TKey &key,
             size_t &opCount) // Вспомогательный метод для удаления узла
                              // (записи) из АВЛ-дерева по ключу. Рекурсивный
                              // метод. Возвращает указатель на корень поддерева
                              // после удаления и балансировки.
  {
    opCount++; // Сравнение указателя (node_ == nullptr).
    if (node_ == nullptr) // Если достигнут nullptr, то узел (запись) не наёден
                          // (так как прошли через лист).
    {
      return nullptr;
    }

    opCount++; // Операция сравнения ключей (key < node_->key).
    if (key < node_->key) {
      opCount++; // Операция присваивания указателя (node_->left = ...).
      node_->left =
          removeNode(node_->left, key,
                     opCount); // Рекурсивно проваливаемся в левое поддерево.
    } else if (key > node_->key) {
      opCount++; // Операция присваивания указателя (node_->right = ...).
      node_->right =
          removeNode(node_->right, key,
                     opCount); // Рекурсивно проваливаемся в правое поддерево.
    } else {
      opCount++; // Операция сравнения ключей (key > node_->key).

      opCount += 3; // Операции сравнения (node_->left == nullptr, && и
                    // node_->left == nullptr).
      if (node_->left == nullptr &&
          node_->right == nullptr) // Если узел (запись) является листом (не
                                   // имеет потомков).
      {
        opCount++; // Операция удаления узла (delete node_).
        delete node_; // Удаляем узел (запись).

        opCount++; // Операция декремента (NodeCount--).
        NodeCount--; // Обновляем количество узлов (записей).

        return nullptr; // Возвращаем nullptr, так как после удаления узла
                        // (записи) его место в дереве становится пустым
                        // (nullptr).
      } else if ((node_->left != nullptr && node_->right == nullptr) ||
                 (node_->left == nullptr &&
                  node_->right !=
                      nullptr)) // Если узел (запись) имеет одного потомка (либо
                                // левого, либо правого).
      {
        opCount += 7; // Операция сравнения в первой ветке else if.

        opCount += 3; // Операции присваивания (Node* childNode = ...), проверки
                      // условия (node_->left == nullptr) и тернарный оператор.
        Node *childNode =
            (node_->left == nullptr)
                ? node_->right
                : node_->left; // Сохраняем указатель на единственного потомка
                               // узла (записи).

        opCount++; // Операция удаления узла (delete node_).
        delete node_; // Удаляем узел (запись).

        opCount++; // Операция декремента (NodeCount--).
        NodeCount--; // Обновляем количество узлов (записей).

        return childNode; // Возвращаем указатель на единственного потомка
                          // удалённого узла (записи), который займет его место
                          // в дереве.
      } else if (node_->left != nullptr &&
                 node_->right != nullptr) // Если узел (запись) имеет двух
                                          // потомков (и левого, и правого).
      {
        opCount += 7; // Операция сравнения в первой ветке else if.
        opCount += 3; // Операции сравнения во второй ветке else if.

        opCount++; // Операция присваивания (Node* maxNodeLeftSubTree = ...).
        Node *maxNodeLeftSubTree =
            maxNode(node_->left,
                    opCount); // Находим узел (запись) с максимальным ключом в
                              // левом поддереве удаляемого узла (записи).

        // Копируем максимальный по ключу узел (запись) из левого поддерева в
        // удаляемый узел (запись):
        opCount++; // Операция присваивания (node_->key = ...).
        node_->key = maxNodeLeftSubTree->key;
        opCount++; // Операция присваивания (node_->value = ...).
        node_->value = maxNodeLeftSubTree->value;

        opCount++; // Операция присваивания (node_->left = ...).
        node_->left = removeNode(
            node_->left, maxNodeLeftSubTree->key,
            opCount); // Рекурсивно удаляем узел (запись) с максимальным ключом
                      // из левого поддерева, так как его значение уже
                      // скопировано в удаляемый узел (запись).
      }
      opCount += 7; // Операция сравнения в первой ветке else if.
      opCount += 3; // Операции сравнения во второй ветке else if.
    }
    opCount++; // Операция сравнения ключей (key > node_->key).

    return balancingTree(
        node_, opCount); // Запуск балансировки АВЛ-дерева после удаления узла
                         // (записи). Балансировка производится со всеми узлами,
                         // которые встретились на пути: от места удаления до
                         // корня (рекурсивно).
  }

  void clearTree(
      Node *node_) // Вспомогательный метод для очистки АВЛ-дерева от всех узлов
                   // (записей). Рекурсивный метод. Удаляет все узлы (записи) в
                   // поддереве, корнем которого является node_.
  {
    if (node_ ==
        nullptr) // Если узел (запись) равен nullptr, то достигнут конец дерева
                 // (прошли через лист). Тогда возвращаемся назад по рекурсии и
                 // начинаем удалять узлы (записи) на пути обратно к корню.
    {
      return;
    }

    clearTree(node_->left); // Рекурсивно очищаем левое поддерево.
    clearTree(node_->right); // Рекурсивно очищаем правое поддерево.

    delete node_; // Удаляем текущий узел (запись).
  }

public:
  AVLTable() : root(nullptr), NodeCount(0) {}

  void clear() override {
    clearTree(root); // Вызываем вспомогательный метод для очистки АВЛ-дерева от
                     // всех узлов (записей), начиная с корня (root).
    root = nullptr; // Обновляем указатель на корень.
    NodeCount =
        0; // Обнуляем количество узлов (записей) в АВЛ-дереве после очистки.
  }

  ~AVLTable() { clear(); }

  std::string getTableName() const override { return "AVLTable"; }

  size_t size() const override { return NodeCount; }

  size_t insert(const TKey &key, const TValue &value) override {
    size_t opCount = 0; // Счётчик количества операций.

    root = insertNode(
        root, key, value,
        opCount); // Обновляем указатель на корень после вставки узла (записи).
    return opCount;
  }

  FindResult find(const TKey &key) override {
    size_t opCount = 0; // Счётчик количества операций.
    FindResult result; // Объект стурктуры для хранения результата поиска.

    opCount++; // Операция присваивания (current_node = ...).
    Node *current_node =
        findNode(root, key,
                 opCount); // Получаем результат поиска узла (записи) по ключу.

    opCount++; // Операция сравнения указателя (current_node != nullptr).
    if (current_node != nullptr) // Если запись найдена.
    {
      opCount += 2; // Операции взятия адреса (&(current_node->value)) и
                    // присваивания (result.value = ...).
      result.value = &(current_node->value); // Указатель на значение найденной
                                             // записи (current_node->value).

      opCount++; // Операция присваиввния (result.operationsCount = opCount).
      result.operationsCount =
          opCount; // Количество операций, произведённых при поиске записи.

      return result; // Возвращаем результат поиска.
    }

    opCount++; // Операция присваиввния (result.operationsCount = opCount).
    result.operationsCount = opCount; // Количество операций, произведённых при
                                      // поиске записи (Но запись не наёдена).
    return result; // Возвращаем результат поиска (Запись не найдена, указатель
                   // на значение равен nullptr).
  }

  size_t remove(const TKey &key) override {
    size_t opCount = 0; // Счётчик количества операций.

    root = removeNode(
        root, key,
        opCount); // Обновляем указатель на корень после удаления узла (записи).
    return opCount;
  }
};