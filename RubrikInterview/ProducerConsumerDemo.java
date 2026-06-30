import java.util.concurrent.*;

class Job {
    private final String id;

    public Job(String id) {
        this.id = id;
    }

    public String getId() {
        return id;
    }
}

class Producer implements Runnable {

    private final BlockingQueue<Job> queue;

    public Producer(BlockingQueue<Job> queue) {
        this.queue = queue;
    }

    @Override
    public void run() {

        int count = 1;

        try {

            while (true) {

                Job job = new Job("JOB-" + count++);

                queue.put(job);

                System.out.println(
                        "Produced: " + job.getId());

                Thread.sleep(1000);
            }

        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}

class Consumer implements Runnable {

    private final BlockingQueue<Job> queue;

    public Consumer(BlockingQueue<Job> queue) {
        this.queue = queue;
    }

    @Override
    public void run() {

        try {

            while (true) {

                Job job = queue.take();

                process(job);
            }

        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    private void process(Job job) {

        System.out.println(
                "Consumed: " + job.getId());
    }
}

public class ProducerConsumerDemo {

    public static void main(String[] args) {

        BlockingQueue<Job> queue =
                new ArrayBlockingQueue<>(10);

        Thread producer =
                new Thread(new Producer(queue));

        Thread consumer =
                new Thread(new Consumer(queue));

        producer.start();
        consumer.start();
    }
}