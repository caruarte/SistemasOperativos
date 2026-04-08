// tenemos definido el struct PCB
struct PCB {
    int STAT; // valores posibles KE_RUNNING, KE_READY, KE_BLOCKED, KE_NEW
    int P_ID; // process ID
    int PC; // valor del PC del proceso al ser desalojado
    int RO; // valor del registro R0 al ser desalojado
    ...
    int R15; // valor del registro R15 al ser desalojado
    int CPU_TIME // tiempo de ejecución del proceso
}

// esta rutina realiza el cambio de contexto entre dos procesos
Ke_context_switch (PCB* pcb_0, PCB* pcb_1) {
    // actualizamos su estado, está ready ahora
	pcb_0->STAT = KE_READY;
	// guardamos el contexto del proceso que se va
	pcb_0->PC = PC;  // esto vale ya que el lenguaje tiene acceso a los registros del proce
	pcb_0->R0 = R0;
    pcb_0->R1 = R1;
    ...
    pcb_0->R15 = R15;
    pcb_0->CPU_TIME += ke_current_user_time(); // Notar que no se resetea a cero
	// todo lo q se pueda actuslizar en su pcb...

    
	// ponemos en 0 el cronometro
	ke_reset_current_user_time();

    pcb_1->STAT = KE_RUNNING
	
	// cargamos el contexto del siguiente proceso, es decir

	PC = pcb_1->PC;
    R0 = pcb_1->R0;
    R1 = pcb_1->R1;
    ...
    R15 = pcb_1->R15;
	
	// Avisamos al sistema qué proceso corre
	set_current_process(pcb_1->P_ID);


    // no se como funciona ret
    // SP = SP - 1;        // decrementar el stack pointer
    // *SP = pcb_1->PC;    // colocar el valor en el tope de la pila
    ret()
}
	
	