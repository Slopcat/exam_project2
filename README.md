# exam_project
финальный проест в skillbox по с++.<br>
поиск слов в файлах.<br>
используется версия:<br>
![GitHub author](https://img.shields.io/badge/C++-17-005199?style=for-the-badge)<br>
![GitHub author](https://img.shields.io/badge/CMake-3.19-005199?style=for-the-badge)<br>
https://cmake.org/<br>
![GitHub author](https://img.shields.io/badge/JSON-3.10.5-orange?style=for-the-badge)<br>
https://github.com/nlohmann/json<br>
![GitHub author](https://img.shields.io/badge/GTest-1.11.0-green?style=for-the-badge)<br>
https://github.com/google/googletest<br>
запускался и тестировалася код в Visual Studio 2019.<br>

* config.json<br>
Файл, в котором указаны название и версия приложения.<br>
Здесь вы также можете изменить максимальное количество релевантных страниц, которые будут помещены в config.json (max_responses).<br>
Содержимое по умолчанию:<br>
```json
{
    "config": 
    {
        "name": "FileSearchEngine",
        "version": "0.1",
        "max_responses": 5
    },
    "files": 
    [
        "resources/file001.txt",
        "resources/file002.txt"
    ]
}
```

* requests.json<br>
Файл, в котором указаны запросы для поиска.<br>
Каждый отдельный запрос следует вводить после "," в новой строке. Пример ниже.<br>
Пример содержимого:<br>
```json
{
    "requests":
    [
        "tiger fox",
        "wolf bird",
        "monkey"
    ]
}
```
* answers.json<br>
Файл, в который будет записан результат поиска в формате JSON.<br>
Пример содержимого:<br>
```json
{
  "answers": {
    "request0": {
      "relevance": [
        {
          "docid": 1,
          "rank": 1.0
        },
        {
          "docid": 0,
          "rank": 0.6700000166893005
        }
      ],
      "result": true
    },
    "request1": {
      "relevance": [
        {
          "docid": 0,
          "rank": 1.0
        },
        {
          "docid": 1,
          "rank": 1.0
        }
      ],
      "result": true
    },
    "request2": {
      "docid": 1,
      "rank": 1.0,
      "result": true
    }
  }
}
```
<i>NOTE:<br>docid - identificator of a relevant document,<br>rank - relative index,<br>result - true (if relevance is found), or false (if document absolutely not relevant for certain request).</i>
