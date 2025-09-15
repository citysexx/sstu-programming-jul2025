FROM gcc:14.3.0

WORKDIR /app

# Копируем исходники
COPY src/ ./src/
COPY main.c ./

RUN gcc -o app main.c src/*.c

# Запуск
CMD ["./app"]
