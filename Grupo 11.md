# Grupo 11

## Cliente

* ClientMain: ver como mejorar la composición

* ProxyClient: Constantes hardcodeadas

* ¿GameBuilder? ¿Client.h?

* mainView: update: Primero procesar y después renderizar, total sólo se va a ver el último renderizado

* wormView: update()

* Escenario: ¿Y esa viga?

* Vistas varias: SDL_QueryTexture(), usarlo dentro de una clase Texture que funcione de wrapper

* TextManager: rutas de las fuentes son relativas

* ¿Sprite debería tener una shape?

* **General**: constantes hardcodeadas, strings pasados por copia, falta documentar clases, ni un const

## Servidor

* Constructores de las armas, muy complejos

* ContactListener (pasar implementación un cpp)

* Gusano: tiene mucha lógica distinta toda junta

* Hay news innecesarios (ej, projectile, water)

* Turn::play()

* **General**: El código está muy acoplado a box2d, hay código de prueba, constantes hardcodeadas, falta documentar clases, ni un const
