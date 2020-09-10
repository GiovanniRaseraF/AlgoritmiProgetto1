import Algorithms.Algorithms;
import Algorithms.HeapSelect;
import Algorithms.MedianOfMediansSelect;
import Algorithms.QuickSelect;

import java.util.ArrayList;
import java.util.Arrays;

public class Main {
    public static void main(String[] args) {

        //Algorithms declaration
        MedianOfMediansSelect medianOfMediansSelect = new MedianOfMediansSelect();
        HeapSelect heapSelect = new HeapSelect();
        QuickSelect quickSelect = new QuickSelect();
        ArrayList<Algorithms> algorithms = new ArrayList<>();
        algorithms.add(quickSelect);
        algorithms.add(heapSelect);
        algorithms.add(medianOfMediansSelect);


        //Initial variable setup
        long minSize = 100;
        long maxSize = 5000000;
        long samples = 100;
        int currentSize;
        int repetitions = 50;
        double error = 0.01; // Max error for time
        double resolution = getMachineBasedTimeResolution();
        RandomArray arrayGenerator = new RandomArray();


        // Repeat samples time
        for (int i = 0; i < samples; i++) {

            // Get size based on difference between min and max size
            double base = Math.exp((Math.log(maxSize) - Math.log(minSize)) / (samples - 1));
            currentSize = (int) ((double) minSize * Math.pow(base, i));

            int k = currentSize / 10;
            int[] randomArray = arrayGenerator.newArray(currentSize);
            heapSelect.setFromSize(randomArray.length);
            ArrayList<Double> tempMemory = new ArrayList<>();
            System.out.print(currentSize + " " + k);

            for (int algo = 0; algo < algorithms.size(); algo++) {

                double deviation = 0d;
                double median = 0d;
                double currentTime;

                for (int rep = 0; rep < repetitions; rep++) { //Repeat the test repetitions time to increase precision
                    currentTime = computeAlgoTime(algorithms.get(algo), randomArray, resolution, error, k) / 1000;
                    median += currentTime;
                    tempMemory.add(currentTime); //Store every time
                }

                median = median / repetitions;
                for (Double aDouble : tempMemory) {
                    deviation += Math.pow(aDouble - median, 2);
                }
                deviation = Math.sqrt(deviation / repetitions);
                System.out.print(" " + median + " " + deviation);

            }
            System.out.println();

        }
    }

    private static double getMachineBasedTimeResolution() {
        long startT, endT;
        long[] value = new long[10000];

        for (int i = 0; i < 10000; i++) {
            startT = System.nanoTime();
            do {
                endT = System.nanoTime();
            } while (startT == endT);
            value[i] = endT - startT;
        }
        Arrays.sort(value);
        return value[value.length / 2];
    }

    private static double computeAlgoTime(Algorithms singleAlgorithm, int[] array, double risoluzione, double errMin, int k) {

        long timeS, timeE;
        int c = 0;
        int[] copiaArr;
        timeS = System.nanoTime();
        do {
            copiaArr = Arrays.copyOf(array, array.length);
            singleAlgorithm.findK(copiaArr, k-1);

            timeE = System.nanoTime();
            c++;
        } while (timeE - timeS <= risoluzione * (1.0 / errMin) + 1.0);
        return ((timeE - timeS) / c);
    }
}
