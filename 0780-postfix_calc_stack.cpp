// postfix_calc_stack.cpp
// Реализация калькулятора с поддержкой четырёх арифметических действий,
// принимающего выражения в постфиксной записи (она же "обратная польская нотация").
// Грамматика выражения: операнд операнд операция, где операнд может быть числом или опять выражением
// Например, 4 3 2 * + ==> 4 + (3 * 2) == 10
// От postfix_calc.cpp отличается тем, что вместо рекурсии и неявного использования стека вызовов
// для хранения промежуточных результатов (операндов) используется явный стек чисел в виде
// статического массива (размер зафиксирован в момент компиляции).
#include <iostream>
#include <cstring> // strchr
using namespace std;

// Читает выражение из потока cin, возвращает вычисленное значение.
double postfix()
{
  static const unsigned STACK_SIZE = 1024; // Размер стека.
  double operand[STACK_SIZE]; // Стек (на основе массива).
  unsigned operand_top = 0; /* Индекс элемента массива, 
    который станет вершиной стека при добавлении элемента. */

  while (true)
  {
    // Операция?
    char op;
    if (cin >> op)
    {
      double z;
      if (strchr("+-*/", op))
      {
        // Убедиться, что в стеке есть хотя бы два числа.
        if (operand_top < 2)
        {
          cerr << "stack underflow: at least 2 items are needed\n";
          break;
        }

        // Извлечь операнды (для сокращения записи).
        const double
          x = operand[operand_top - 2],
          y = operand[operand_top - 1];
        operand_top -= 2;

        // Вычислить значение выражения (операнды уже известны -- x, y).
        switch (op)
        {
        case '+': z = x + y; break;
        case '-': z = x - y; break;
        case '*': z = x * y; break;
        case '/': z = x / y; break;
        }

        // Записать новое значение в стек.
        operand[operand_top++] = z;

        // Проверить переполнение стека.
        if (operand_top == STACK_SIZE)
        {
          cerr << "stack overflow\n";
          break;
        }
      }
      else // Не операция? вернуть считанный символ в поток.
      {
        cin.unget();
        // Число?
        if (cin >> z)
        {
          // Записать новое значение в стек.
          operand[operand_top++] = z;

          // Проверить переполнение стека.
          if (operand_top == STACK_SIZE)
          {
            cerr << "stack overflow\n";
            break;
          }
        }
        else // Ошибка ввода.
          break;
      }
    }
    else // Ошибка ввода.
      break;
  }

  // Вернуть текущую вершину стека.
  if (operand_top == 0) // Стек пуст.
  {
    cerr << "stack underflow: at least 1 item is needed\n";
    return 0.;
  }
   
  return operand[operand_top - 1];
}


int main()
{
  while (true)
  {
    double answer = postfix();
    // Сброс потока.
    cin.clear();
    cin.ignore(cin.rdbuf()->in_avail());
    cin.sync();
    // Вывод ответа.
    cout << "answer = " << answer << endl;
  }
  return EXIT_SUCCESS;
}