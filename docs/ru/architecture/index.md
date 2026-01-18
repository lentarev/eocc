[<= Назад](../) 

# Архитектура

Движок **eocc** построен вокруг трёх ключевых принципов:

1. **Прозрачность** — никаких скрытых систем; всё можно прочитать и понять.
2. **Модульность** — каждая часть (сцена, рендерер, камера) заменяема.
3. **Контроль** — разработчик решает, что и как рисовать, без «магии».

## Основные компоненты

### `Engine`
Центральный класс, который:
- Создаёт окно через GLFW,
- Управляет текущей сценой,
- Запускает главный цикл с фиксированным шагом (`fixed timestep`),
- Обеспечивает доступ к системам (ввод, рендеринг).

### `SceneBase`
Абстрактный базовый класс для всех сцен.  
Каждая сцена (меню, уровень, настройки) наследуется от него и реализует:
- `init()` — однократная инициализация,
- `update(float dt, float time)` — логика и физика,
- `render()` — отрисовка через `Renderer`.

> Сцены полностью изолированы: ресурсы (шейдеры, мешы) загружаются и освобождаются внутри них.

### `Renderer`
Отвечает за:
- Очистку буфера,
- Привязку шейдеров,
- Отправку геометрии в GPU.

> В eocc нет «рендер-графа» или сложных пайплайнов — только прямой вызов OpenGL. Это даёт полный контроль.

### `Camera`
Реализует:
- Перспективную проекцию,
- Матрицу вида,
- Автоматическую адаптацию под изменение размера окна.

## Жизненный цикл

1. `main()` создаёт `Engine`.
2. `Engine` инициализирует GLFW, GLAD, окно.
3. Устанавливается начальная сцена (например, `Menu`).
4. Запускается цикл:
   - Обработка ввода,
   - Фиксированный `update` (физика),
   - Переменный `render` (графика).
5. При переходе между сценами старая освобождает ресурсы, новая — инициализируется.

## Структура проекта

```text
eocc/
├── demo/                 # Demo application (game example)
│   ├── main.cpp          # Entry point
│   ├── scenes/           # Game-specific scenes (Menu, Level1, etc.)
│   └── shaders/          # GLSL shaders for the demo
│
├── include/eocc/         # Public API headers (installable)
│   ├── Engine.h
│   ├── base/
│   ├── camera/
│   ├── renderer/
│   ├── scene/
│   └── system/
│
└── src/eocc/             # Engine implementation
    ├── Engine.cpp
    ├── base/
    ├── camera/
    ├── renderer/
    └── system/
```

Чтобы использовать eocc в своём проекте:
1. Скопируй `include/eocc/` в свой проект,
2. Слинкуй с `libeocc_engine.a` (или добавь исходники),
3. Наследуй `SceneBase` и передай экземпляр в `Engine::setCurrentScene()`.

## Пример: создание сцены

```cpp
class MyScene : public eocc::SceneBase {
public:
    void init(eocc::Engine* engine) override {
        // Загрузка шейдеров, мешей
    }

    void update(float dt, float t) override {
        // Логика
    }

    void render() override {
        engine->getRenderer().submit(mesh, shader);
    }
};

// В main.cpp:

int main() {
    // 1. Global Initialization (GLFW)
    if (!glfwInit()) {
        return -1;
    }

    try {
        const auto engine = std::make_unique<eocc::Engine>();
        engine->setCurrentScene(std::make_unique<Menu>());
        engine->run();

    } catch (const std::exception& e) {
        eocc::Logger::log(1, "Fatal error: %s\n", e.what());
        return -1;
    }

    // Freeing up all resources associated with GLFW
    glfwTerminate();

    return 0;
}
```

> Это всё. Никаких макросов, рефлексии или скрытых регистраций.