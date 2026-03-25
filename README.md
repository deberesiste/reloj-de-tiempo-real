# reloj-de-tiempo-real
Sistema con ESP32 que utiliza el RTC interno para automatizar el encendido y apagado de un LED basado en tiempo.

Descripción del proyecto

Sistema basado en el microcontrolador ESP32 que utiliza el RTC interno (Real Time Clock) para controlar el encendido y apagado de un LED en horarios definidos.

El proyecto demuestra el uso de temporización sin depender de conexión externa, ideal para automatización básica.

🎯 Objetivos
Implementar el uso del RTC interno del ESP32
Automatizar el encendido/apagado de un LED
Comprender la gestión del tiempo en sistemas embebidos
⚙️ Tecnologías utilizadas
ESP32
Arduino IDE
RTC interno del ESP32
🔧 Funcionamiento

El sistema utiliza el reloj interno del ESP32 para ejecutar acciones programadas:

Se configura una hora inicial
El RTC mantiene el conteo del tiempo
Cuando se cumple la condición programada:
El LED se enciende o apaga automáticamente
🔌 Conexiones
Componente	Pin ESP32
LED	GPIO (ej: 2)
GND	GND

▶️ Video demostración

Puedes ver el funcionamiento del proyecto en el siguiente enlace:

👉 https://www.youtube.com/watch?v=ZFyUBS0Erhc

📂 Estructura del proyecto

🚀 Cómo ejecutar
Instalar Arduino IDE
Configurar la placa ESP32
Cargar el código
Subir al dispositivo
Observar el comportamiento del LED

📊 Aplicaciones
Automatización de iluminación
Sistemas IoT básicos
Proyectos educativos
Domótica

👨‍💻 Autores

Robert Borja - Paul Romero -Michael Ortega
