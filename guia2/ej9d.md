Por más que Shortest Remaining Time First tiene un menor Turnaround, en este caso, que Round Robin en el caso de tener un sistema en el cual se van agregando procesos cortos muy seguido usar SRTF puede generar Starvation de procesos más largos como procesos Batch. Y tambien si tenemos muchos procesos interactivos o real-time el tener que esperar tanto para poder ejecutarse genera que no se sientan responsivos esos procesos.

Tambien en la practica no es fácil estimar el tiempo restante de un proceso para usar SRTF.

Tiene sentido utilizar políticas como Round-Robin en los siguientes contextos:

Sistemas Interactivos (Desktop/Time-Sharing): En este contexto, el parámetro crítico no es el turnaround global del proceso, sino el tiempo de respuesta. Round-Robin garantiza que ningún proceso espere más de $(N-1) \times quantum$ para empezar a mostrar resultados. Esto es vital para que un usuario sienta que la interfaz gráfica o la terminal responden rápido, sin quedarse congeladas. SRTF perjudicaría enormemente a los procesos interactivos si hay procesos cortos monopolizando la CPU.

Prevención de Inanición (Starvation): SRTF sufre de inanición. Si ingresa un flujo constante de procesos de ráfaga corta, los procesos de ráfaga larga (CPU-bound) nunca se ejecutarán. En cambio, Round-Robin es justo ("fair") por naturaleza; todos los procesos progresan eventualmente.

Sistemas Batch vs. Real-Time: SRTF brilla en sistemas Batch (procesamiento por lotes) donde el objetivo es maximizar la cantidad de trabajos terminados por hora (throughput) y no importa la interactividad, siempre que se conozcan los tiempos de CPU de antemano. 

Para sistemas Real-Time, ni RR simple ni SRTF son ideales, ya que requieren algoritmos que ofrezcan garantías determinísticas sobre plazos de tiempo (como Rate Monotonic o Earliest Deadline First), aunque una variante de RR priorizado se suele usar para tareas en segundo plano no críticas.