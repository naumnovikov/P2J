# P2J

P2J — это простой конвертер из PCAP в JSON.

## Что умеет

- читает `.pcap` файл
- извлекает базовую информацию о пакетах
- пишет результат в JSON

## Сборка

```bash
cd /Users/naumnovikov/Desktop/P2J
cmake -S . -B build
cmake --build build
```

## Запуск

```bash
./build/P2J test.pcap
```

или с кастомным выходным файлом:

```bash
./build/P2J test.pcap packets.json
```

## Пример JSON

```json
{
  "meta": {
    "source_file": "test.pcap",
    "captured_at": "2026-09-30T12:00:00Z",
    "packet_count": 1
  },
  "packets": [
    {
      "timestamp": "2026-09-30T12:00:00Z",
      "length": 64
    }
  ]
}
```

## Тесты

```bash
cd /Users/naumnovikov/Desktop/P2J
ctest --test-dir build --output-on-failure
```

или:

```bash
./build/p2j_tests
```
