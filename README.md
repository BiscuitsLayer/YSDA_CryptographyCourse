# Шифр "Кузнечик"

## Оптимизации
1. Оптимизация умножения - предподсчёт всех умножений в поле Галуа для ускорения линейного преобразования

Для включения добавить в начале *CMakeLists.txt*:
```
add_definitions(-DOPTIMIZATION_LEVEL_1)
```

2. Оптимизация линейного преобразования (описана в [статье](https://habr.com/ru/articles/312224/))

Для включения добавить в начале *CMakeLists.txt*:
```
add_definitions(-DOPTIMIZATION_LEVEL_2)
```


## Математика
[Хабр: Конечное поле GF(256) и немного магии](https://habr.com/ru/articles/279197/)

[Хабр: Криптографический алгоритм «Кузнечик»: просто о сложном](https://habr.com/ru/articles/459004/)

## Код и оптимизации

[Хабр: ГОСТ Р 34.12 '15 на SSE2, или Не так уж и плох Кузнечик](https://habr.com/ru/articles/312224/)

[Хабр: Реализация блочного шифра «Кузнечик» с режимом CFB на С++](https://habr.com/ru/articles/313932/)

## Версия имплементации с оптимизациями
https://github.com/app13y/lg15/tree/master