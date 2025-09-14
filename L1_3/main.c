#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// Підключення математичної бібліотеки (pow, fabs, etc.)
#include <windows.h>
// Підключення Windows API для кольорового виведення в консолі

// Функція для встановлення кольору тексту (для Windows)
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Отримуємо дескриптор консолі для маніпуляцій
    SetConsoleTextAttribute(hConsole, color);
    // Встановлюємо атрибути тексту (колір) для консолі
}

// Функція для обчислення значення f(x)
double calculate_function(double x) {
    return -4 * pow(x, 3) - 3 * pow(x, 2) + 2 * pow(x, 2) - 5 * x - 25;
    // Обчислюємо значення функції: -4x³ - 3x² + 2x² - 5x - 25 = -4x³ - x² - 5x - 25
    // pow(x, 3) - піднесення x до степеня 3
}

// Функція для валідації числового введення
int validate_input(double value, const char* field_name, double min, double max) {
    if (value < min || value > max) {
        // Перевіряємо чи значення знаходиться в допустимому діапазоні
        setColor(12); // Червоний колір для помилок
        printf("Error: %s must be in range [%.2f, %.2f]\n", field_name, min, max);
        // Виводимо повідомлення про помилку з назвою поля та діапазоном
        setColor(7); // Повернення до білого кольору
        return 0; // Повертаємо 0 (невалідне значення)
    }
    return 1; // Повертаємо 1 (валідне значення)
}

// Функція для очищення буфера введення
void clear_input_buffer() {
    while (getchar() != '\n');
    // Читаємо символи з буфера введення до тих пір, поки не зустрінемо символ нового рядка
    // Це запобігає зацикленню при некоректному введенні
}

// Функція для виведення заголовку
void print_header() {
    setColor(11); // Блакитний колір
    printf("====================================================\n");
    printf("    Function Calculator f(x) \n");
    printf("    f(x) = -4x^3 - 3x^2 + 2x^2 - 5x - 25\n");
    printf("    Simplified: f(x) = -4x^3 - x^2 - 5x - 25\n");
    // Виводимо інформацію про функцію
    printf("====================================================\n\n");
    setColor(7); // Повертаємо стандартний колір
}

// Функція для виведення таблиці значень функції
void print_table(double x1, double x2, int n, double delta, int mode) {
    setColor(10); // Зелений колір
    printf("\n====================================================\n");
    printf("               Function Values Table\n");
    printf("====================================================\n");
    printf("      x        |        f(x)\n");
    printf("----------------------------------------------------\n");
    setColor(7); // Повертаємо стандартний колір

    double x = x1; // Поточне значення x
    int count = 0; // Лічильник точок
    double total_sum = 0; // Сума всіх значень функції
    double min_value = calculate_function(x1); // Мінімальне значення функції
    double max_value = min_value; // Максимальне значення функції

    while (x <= x2 + 1e-10) {
        // Цикл виконується поки x не перевищить x2 (з невеликим допуском для плаваючої точки)
        double fx = calculate_function(x); // Обчислюємо f(x)

        // Визначення кольору для значення функції
        if (fx < 0) {
            setColor(12); // Червоний для від'ємних значень
        } else if (fx > 0) {
            setColor(10); // Зелений для додатних значень
        } else {
            setColor(14); // Жовтий для нуля
        }

        printf(" %12.6f | %15.6f\n", x, fx);
        // Виводимо x з 6 знаками після коми та f(x) з 6 знаками

        // Оновлення статистики
        total_sum += fx; // Додаємо поточне значення до загальної суми
        if (fx < min_value) min_value = fx; // Оновлюємо мінімум
        if (fx > max_value) max_value = fx; // Оновлюємо максимум

        setColor(7); // Повернення до нормального кольору

        if (mode == 1) {
            // Режим 1: рівномірний розподіл точок
            x = x1 + (++count) * (x2 - x1) / (n - 1);
            // Обчислюємо наступне x за формулою рівномірного розподілу
        } else {
            // Режим 2: крокове збільшення
            x += delta; // Збільшуємо x на крок delta
            count++; // Збільшуємо лічильник
        }
    }

    setColor(11); // Блакитний колір для статистики
    printf("====================================================\n");
    printf("Statistics:\n");
    printf("Points count: %d\n", count);
    printf("Total sum: %.6f\n", total_sum);
    printf("Minimum value: %.6f\n", min_value);
    printf("Maximum value: %.6f\n", max_value);
    printf("Average value: %.6f\n", total_sum / count);
    // Виводимо статистичну інформацію
    printf("====================================================\n\n");
    setColor(7); // Повертаємо стандартний колір
}

// Функція для знаходження діапазонів зміни знака
void find_sign_changes(double x1, double x2, int n, double delta, int mode) {
    setColor(14); // Жовтий колір
    printf("\n====================================================\n");
    printf(" Intervals where function changes sign\n");
    printf("====================================================\n");
    printf("   Interval (x)     |         Notes\n");
    printf("----------------------------------------------------\n");
    setColor(7); // Повертаємо стандартний колір

    double x = x1; // Поточне значення x
    double prev_fx = calculate_function(x); // Попереднє значення f(x)
    double prev_x = x; // Попереднє значення x
    int count = 0; // Лічильник точок
    int sign_change_count = 0; // Лічильник змін знака

    while (x <= x2 + 1e-10) {
        double fx = calculate_function(x); // Обчислюємо поточне f(x)

        // Перевірка зміни знака
        if (prev_fx * fx < 0) {
            // Якщо добуток попереднього та поточного значень від'ємний - знак змінився
            setColor(13); // Фіолетовий для особливих повідомлень
            printf(" [%8.4f, %8.4f] | f(%.4f)=%7.2f -> f(%.4f)=%7.2f\n",
                   prev_x, x, prev_x, prev_fx, x, fx);
            // Виводимо інформацію про інтервал зміни знака
            sign_change_count++; // Збільшуємо лічильник змін знака
            setColor(7); // Повертаємо стандартний колір
        }

        prev_fx = fx; // Зберігаємо поточне значення як попереднє
        prev_x = x;   // Зберігаємо поточний x як попередній
        count++;      // Збільшуємо лічильник

        if (mode == 1) {
            // Режим 1: рівномірний розподіл
            x = x1 + count * (x2 - x1) / (n - 1);
        } else {
            // Режим 2: крокове збільшення
            x += delta;
        }
    }

    if (sign_change_count == 0) {
        setColor(12); // Червоний колір для повідомлення про відсутність змін
        printf("                    | No sign changes found\n");
        setColor(7); // Повертаємо стандартний колір
    }

    setColor(14); // Жовтий колір
    printf("====================================================\n");
    printf("Sign changes found: %d\n", sign_change_count);
    printf("====================================================\n\n");
    setColor(7); // Повертаємо стандартний колір
}

int main() {
    int choice;       // Змінна для вибору режиму (1 або 2)
    double x1, x2;    // Початкове та кінцеве значення x
    double delta;     // Крок зміни x
    int n;            // Кількість точок

    print_header(); // Виводимо заголовок програми

    // Вибір режиму введення
    while (1) {
        setColor(15); // Яскраво-білий
        printf("Select input method:\n");
        printf("1 - Start value, end value, points count\n");
        printf("2 - Start value, end value, step size\n");
        setColor(11); // Блакитний
        printf("Your choice (1 or 2): ");
        setColor(7); // Стандартний колір

        if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
            // Перевіряємо коректність введення: має бути одне ціле число 1 або 2
            setColor(12); // Червоний для помилок
            printf("Error: enter 1 or 2!\n");
            setColor(7); // Стандартний колір
            clear_input_buffer(); // Очищаємо буфер введення
            continue; // Повторюємо цикл
        }
        break; // Виходимо з циклу при коректному введенні
    }

    // Введення початкових даних
    while (1) {
        setColor(11); // Блакитний
        printf("\nEnter start value X1: ");
        setColor(7); // Стандартний колір
        if (scanf("%lf", &x1) != 1) {
            // Перевіряємо чи введено коректне число
            setColor(12); // Червоний
            printf("Error: enter valid number!\n");
            setColor(7); // Стандартний
            clear_input_buffer(); // Очищаємо буфер
            continue; // Повторюємо
        }

        setColor(11); // Блакитний
        printf("Enter end value X2: ");
        setColor(7); // Стандартний
        if (scanf("%lf", &x2) != 1) {
            setColor(12); // Червоний
            printf("Error: enter valid number!\n");
            setColor(7); // Стандартний
            clear_input_buffer(); // Очищаємо буфер
            continue; // Повторюємо
        }

        if (x2 <= x1) {
            // Перевіряємо чи X2 > X1
            setColor(12); // Червоний
            printf("Error: X2 must be greater than X1!\n");
            setColor(7); // Стандартний
            continue; // Повторюємо
        }

        if (choice == 1) {
            // Режим 1: введення кількості точок
            setColor(11); // Блакитний
            printf("Enter points count N: ");
            setColor(7); // Стандартний
            if (scanf("%d", &n) != 1) {
                setColor(12); // Червоний
                printf("Error: enter valid integer!\n");
                setColor(7); // Стандартний
                clear_input_buffer(); // Очищаємо буфер
                continue; // Повторюємо
            }
            if (!validate_input(n, "N", 2, 100)) {
                // Перевіряємо чи N в діапазоні [2, 10000]
                continue; // Повторюємо при невалідному значенні
            }
            delta = (x2 - x1) / (n - 1); // Обчислюємо крок автоматично
        } else {
            // Режим 2: введення кроку
            setColor(11); // Блакитний
            printf("Enter step size delta: ");
            setColor(7); // Стандартний
            if (scanf("%lf", &delta) != 1) {
                setColor(12); // Червоний
                printf("Error: enter valid number!\n");
                setColor(7); // Стандартний
                clear_input_buffer(); // Очищаємо буфер
                continue; // Повторюємо
            }
            if (!validate_input(delta, "delta", 0.001, x2 - x1)) {
                // Перевіряємо чи delta в діапазоні [0.001, x2-x1]
                continue; // Повторюємо при невалідному значенні
            }
            n = (int)((x2 - x1) / delta) + 1; // Обчислюємо орієнтовну кількість точок
        }

        break; // Виходимо з циклу при успішному введенні всіх даних
    }

    setColor(10); // Зелений колір для параметрів
    printf("\nCalculation parameters:\n");
    printf("X1 = %.4f\n", x1);
    printf("X2 = %.4f\n", x2);
    if (choice == 1) {
        printf("N = %d\n", n);
        printf("delta = %.6f (auto calculated)\n", delta);
    } else {
        printf("delta = %.6f\n", delta);
        printf("N ≈ %d (estimated points count)\n", n);
    }
    setColor(7); // Повертаємо стандартний колір

    // Виведення таблиці значень
    print_table(x1, x2, n, delta, choice);

    // Пошук діапазонів зміни знака
    find_sign_changes(x1, x2, n, delta, choice);

    // Додаткова інформація
    setColor(11); // Блакитний колір
    printf("Additional information:\n");
    printf("- Function: f(x) = -4x^3 - x^2 - 5x - 25\n");
    printf("- Argument range: [%.2f, %.2f]\n", x1, x2);
    printf("- Calculation points: %d\n", n);
    printf("- Step size: %.6f\n", delta);
    printf("\nPress any key to exit...\n");
    setColor(7); // Повертаємо стандартний колір

    getchar(); // Зчитуємо залишковий символ нового рядка
    getchar(); // Чекаємо натискання будь-якої клавіші

    return 0; // Успішне завершення програми
}
