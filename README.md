# Тупо репа с задачками по учебе

Описание: Терминальное приложение с задачками, выполненными для зачета.
Variant 12 - 15

## Требования для запуску

1. UNIX операционная система (`Linux`, `MacOS`);
2. `docker`, `docker-buildx`, 'docker-compose' на системе.

## Инструкция по запуску

1. Клонируйте репозиторий:

```bash
git clone git@github.com:citysexx/sstu-programming-jul2025.git
```

2. Зайдите в репозиторий:

```bash
cd sstu-programming-jul2025/
```

3. Запустите сборку:

```bash
docker compose build
```

4. Запустите приложение:

```bash
docker compose run --rm -it c-app
```
