package myTest;

import recognition.Neuron;



public class TestClass {



    public static void test_number_0() throws Exception {
        Neuron neon = new Neuron();
        neon.setWeightNeuron();

        System.out.print("test_1.0 ");
        neon.set_A(0, 1, 0, 1, 0, 1, 0, 1, 0);
        if(neon.findNumber_1_or_0() != 0) {
            System.out.println("Wrong answer!");
        } else {
            System.out.print("SUCCESS!");
        }
        System.out.println();


        System.out.print("test_2.0 ");
        neon.set_A(1, 1, 1, 1, 0, 1, 0, 1, 0);
        if(neon.findNumber_1_or_0() != 0) {
            System.out.println("Wrong answer!");
        } else {
            System.out.print("SUCCESS!");
        }
        System.out.println();


        System.out.print("test_3.0 ");
        neon.set_A(0, 1, 1, 1, 0, 1, 1, 1, 0);
        if(neon.findNumber_1_or_0() != 0) {
            System.out.println("Wrong answer!");
        } else {
            System.out.print("SUCCESS!");
        }
        System.out.println();


    }
    public static void test_number_1() throws Exception {
        Neuron neon = new Neuron();
        neon.setWeightNeuron();

        System.out.print("test_1.1 ");
        neon.set_A(1, 1, 1, 0, 0, 0, 0, 0, 0);
        if(neon.findNumber_1_or_0() != 1) {
            System.out.println("Wrong answer!");
        } else {
            System.out.print("SUCCESS!");
        }
        System.out.println();


        System.out.print("test_2.1 ");
        neon.set_A(0, 1, 1, 0, 1, 0, 0, 1, 0);
        if(neon.findNumber_1_or_0() != 1) {
            System.out.println("Wrong answer!");
        } else {
            System.out.print("SUCCESS!");
        }
        System.out.println();


    }


}
