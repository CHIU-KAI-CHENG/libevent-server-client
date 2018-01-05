#include "client.hpp"
#include "PWM.hpp"

#include <prussdrv.h>
#include <pruss_intc_mapping.h>
#include <thread>
#include <stdio.h>

void read_cb(bufferevent *bev, void * arg);
void network(Client * client);


int main()
{   

    /* Initialize the network connection*/
    Client * client = new Client(5201, "192.168.0.5", read_cb);
    thread network_thread(network, client);

    sleep(1);



	/* Initialize the PRU */
	cout << ">> Initializing PRU" << endl;
	tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;
	prussdrv_init();

	/* Open PRU Interrupt */
	if (prussdrv_open (PRU_EVTOUT_0)) {
		// Handle failure
		cerr << ">> PRU open failed" << endl;;
		return 1;
	}

	/* Get the interrupt initialized */
	prussdrv_pruintc_init(&pruss_intc_initdata);

	/* Get pointers to PRU local memory */
	void *pruDataMem;
	prussdrv_map_prumem(PRUSS0_PRU0_DATARAM, &pruDataMem);
	unsigned int *pruData = (unsigned int *) pruDataMem;

	/* Execute code on PRU */
	cout << ">> Executing HCSR-04 code" << endl;
	prussdrv_exec_program(0, "hcsr04.bin");

	/* Get measurements */
	int i = 0;
    float dis = 0;

	while (i++ < 20) {
		
		// Wait for the PRU interrupt
		prussdrv_pru_wait_event (PRU_EVTOUT_0);
		prussdrv_pru_clear_event(PRU_EVTOUT_0, PRU0_ARM_INTERRUPT);
		
		// Print the distance received from the sonar
		// At 20 degrees in dry air the speed of sound is 342.2 cm/sec
		// so it takes 29.12 us to make 1 cm, i.e. 58.44 us for a roundtrip of 1 cm
        dis = (float) pruData[0] / 58.44;
		printf("%3d: Distance = %.2f cm\n", i, (float) pruData[0] / 58.44);

        if (dis < 100)
        {
            system("echo 2500000 > /sys/class/pwm/pwm0/duty_ns");
            system("espeak -v zh \"垃圾桶滿了，請到附近最近的垃圾桶丟垃圾\" -s 160 --stdout | aplay");
            client -> Write("trashcan|full");
        }
        else
        {
            system("echo 600000 > /sys/class/pwm/pwm0/duty_ns");
        }
		sleep(1);
	}

	/* Disable PRU and close memory mapping*/
	prussdrv_pru_disable(0);
	prussdrv_exit();
	printf(">> PRU Disabled.\r\n");




    network_thread.join();


 

    
    return 0;
}

void network(Client * client)
{
    client -> Connect();
}

void read_cb(bufferevent *bev, void * arg)
{

}