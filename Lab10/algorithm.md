# Алгоритм определения функциональности графа

> **Примечание.** *Курсивом* будут выделены части, которые не должы входить
в итоговый отчёт, но нужны только для пояснения

0. Задаём количество вершин графа. *По идее, это можно и опустить. В коде не задаётся явно количество вершин. Оно выясняется на основе введённых данных.*

1. Заполняется матрица инцидентности графа.

2. Считается количество вершин, имеющих ровно одно исходящее ребро *(Если более подробно, то можно заменить на "Считается количество вершин, у которых размер списка смежных вершин равен 1", но как-то некрасиво)*

3. Если полученное количество равно порядку графа и это количество больше 0, то граф является функциональным.

4. Иначе, если полученное количество равно 0, то граф является контрафункциональным.

5. Иначе граф не является ни функциональным, ни контрафункциональным.

6. Выводим результат в консоль.
