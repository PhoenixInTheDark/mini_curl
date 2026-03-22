# mini-curl

> **Status: Work in Progress** — the project is under active development.

A minimal command-line HTTP client written in C from scratch, inspired by [curl](https://curl.se/). The goal is to support GET and POST requests over HTTP and HTTPS without any third-party HTTP libraries.

---

## Usage (planned)

```sh
# GET request
./curl http://example.com/api/data

# GET with custom header
./curl -H "Accept: application/json" http://example.com/api/data

# POST with body
./curl -X POST -H "Content-Type: application/json" -d '{"key":"value"}' http://example.com/api

# HTTPS
./curl https://example.com/secure
```

---

## Options

| Flag | Description |
|------|-------------|
| `-X <METHOD>` | HTTP method (`GET`, `POST`) |
| `-H <header>` | Add a request header (can be used multiple times) |
| `-d <body>` | Request body (implies POST if `-X` is not set) |

---

## What is done

- [x] **URL parsing** — scheme, host, port, path extraction
- [x] **TLS detection** — distinguishes `http://` from `https://`
- [x] **IP parsing** — extracts a raw IP address from the URL
- [x] **Domain name detection** — tells apart a bare IP from a hostname
- [x] **Port parsing** — reads port from URL or falls back to default
- [x] **Path parsing** — extracts the URL path (defaults to `/`)
- [x] **CLI argument parsing** — `-X`, `-H`, `-d` flags
- [x] **Request struct** — internal `request_t` with all fields populated
- [x] **Makefile** — build system with `all`, `clean`, `run` targets

## What is planned

- [ ] **DNS resolution** — resolve domain names to IP addresses
- [ ] **TCP connection** — open a raw socket and connect to the server
- [ ] **TLS/SSL support** — encrypted connections via `openssl` or `mbedtls`
- [ ] **HTTP request builder** — assemble a valid HTTP/1.1 request string
- [ ] **Send request** — write the request over the socket
- [ ] **Receive response** — read and parse the server response
- [ ] **Response output** — print headers and body to stdout
- [ ] **POST support** — send a body with correct `Content-Length`
- [ ] **Redirect following** — handle `301`/`302` responses

---

## Build

```sh
make        # build → ./src/curl
make clean  # remove build artifacts
make run    # build and run
```

Requires GCC and a POSIX-compatible system (Linux / macOS).

---

---

# mini-curl (RU)

> **Статус: В разработке** — проект активно развивается.

Минималистичный HTTP-клиент для командной строки, написанный на C с нуля по мотивам [curl](https://curl.se/). Цель — поддержка GET и POST запросов по HTTP и HTTPS без сторонних HTTP-библиотек.

---

## Использование (планируется)

```sh
# GET запрос
./curl http://example.com/api/data

# GET с кастомным заголовком
./curl -H "Accept: application/json" http://example.com/api/data

# POST с телом запроса
./curl -X POST -H "Content-Type: application/json" -d '{"key":"value"}' http://example.com/api

# HTTPS
./curl https://example.com/secure
```

---

## Флаги

| Флаг | Описание |
|------|----------|
| `-X <METHOD>` | HTTP-метод (`GET`, `POST`) |
| `-H <header>` | Добавить заголовок запроса (можно указывать несколько раз) |
| `-d <body>` | Тело запроса |

---

## Что уже сделано

- [x] **Парсинг URL** — извлечение схемы, хоста, порта, пути
- [x] **Определение TLS** — различает `http://` и `https://`
- [x] **Парсинг IP** — извлекает голый IP-адрес из URL
- [x] **Определение доменного имени** — отличает IP-адрес от доменного имени
- [x] **Парсинг порта** — читает порт из URL
- [x] **Парсинг пути** — извлекает путь из URL (по умолчанию `/`)
- [x] **Парсинг аргументов CLI** — флаги `-X`, `-H`, `-d`
- [x] **Структура запроса** — внутренняя `request_t` со всеми заполненными полями
- [x] **Makefile** — система сборки с целями `all`, `clean`, `run`

## Что планируется

- [ ] **DNS-резолвинг** — преобразование доменных имён в IP-адреса
- [ ] **TCP-соединение** — открытие сокета и подключение к серверу
- [ ] **Поддержка TLS/SSL** — шифрованные соединения через `openssl` или `mbedtls`
- [ ] **Сборка HTTP-запроса** — формирование корректной HTTP/1.1 строки запроса
- [ ] **Отправка запроса** — запись запроса в сокет
- [ ] **Получение ответа** — чтение и разбор ответа сервера
- [ ] **Вывод ответа** — печать заголовков и тела в stdout
- [ ] **Поддержка POST** — отправка тела с корректным `Content-Length`
- [ ] **Следование редиректам** — обработка ответов `301`/`302`

---

## Сборка

```sh
make        # сборка → ./src/curl
make clean  # удалить артефакты сборки
make run    # собрать и запустить
```

Требуется GCC и POSIX-совместимая система (Linux / macOS).
