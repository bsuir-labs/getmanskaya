Для решения задачи необходимы переменные:

* n - количество вершин
* m - количество рёбер
* graph - множество, которое содержит рёбра графа
* NotChecked - множество непроверенных вершин обрабатываемого графа
* FunctionalNodes - множество, которое будет содержать вершины, для которых выполняется условие функциональности
* CurrentNode - переменная, которая содержит текущую обрабатываемую вершину

### Вход

![img0](https://github.com/bsuir-labs/getmanskaya/raw/master/Lab10/shitty/exp/img0.png)

### Шаг 1

Создаём и заполняем множество рёбер графа

![img1](https://github.com/bsuir-labs/getmanskaya/raw/master/Lab10/shitty/exp/img1.png)

### Шаг 2

Создаём и заполняем множество непроверенных вершин

![img2](https://github.com/bsuir-labs/getmanskaya/raw/master/Lab10/shitty/exp/img2.png)

### Шаг 3

Создаём множество, которое будет содержать вершины, для которых выполняется условие функциональности

![img3](https://github.com/bsuir-labs/getmanskaya/raw/master/Lab10/shitty/exp/img3.png)

### Шаг 4

Из множества непроверенных вершин достаём вершину (A) и помещаем её в переменную CurrentNode. Удаляем эту вершину из множества NotChecked.

![img4](https://github.com/bsuir-labs/getmanskaya/raw/master/Lab10/shitty/exp/img4.png)

### Шаг 5

Проверяем условие функциональности. Полустепень исхода вершины равна 1. Помещаем вершину в множество FunctionalNodes.

![img5](https://github.com/bsuir-labs/getmanskaya/raw/master/Lab10/shitty/exp/img5.png)

### Шаг 6

Из множества NotChecked достаём вершину (B) и помещаем её в переменную CurrentNode. Удаляем эту вершину из множества NotChecked. Так как условие функциональности выполняется, помещаем вершину (В) в множество FunctionalNodes.

![img6](https://github.com/bsuir-labs/getmanskaya/raw/master/Lab10/shitty/exp/img6.png)

### Шаг 7

Из множества NotChecked достаём вершину (C) и помещаем её в переменную CurrentNode. Удаляем эту вершину из множества NotChecked. Так как условие функциональности выполняется, помещаем вершину (C) в множество FunctionalNodes.

![img7](https://github.com/bsuir-labs/getmanskaya/raw/master/Lab10/shitty/exp/img7.png)

### Шаг 8

Из множества NotChecked достаём вершину (D) и помещаем её в переменную CurrentNode. Удаляем эту вершину из множества NotChecked. Так как условие функциональности выполняется, помещаем вершину (D) в множество FunctionalNodes.

![img8](https://github.com/bsuir-labs/getmanskaya/raw/master/Lab10/shitty/exp/img8.png)

### Шаг 9

Из множества NotChecked достаём вершину (Е) и помещаем её в переменную CurrentNode. Удаляем эту вершину из множества NotChecked. Так как условие функциональности выполняется, помещаем вершину (Е) в множество FunctionalNodes.

![img9](https://github.com/bsuir-labs/getmanskaya/raw/master/Lab10/shitty/exp/img9.png)

### Шаг 10

Множество NotChecked пусто. Результат работы алгоритма: граф является функциональным, так как размер множества FunctionalNodes равен n, а значит, что для всех вершин в графе выполняется условие.