
import java.util.ArrayDeque;
import java.util.Queue;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

class Job{
    String id;

    public Job(String id) {
        this.id = id;
    }
    
}

class JobQueue{
    private final Queue<Job> queue;
    private final int cap;
    private final ReentrantLock lock;
    private final Condition notEmpty;
    private final Condition notFull;

    public JobQueue(Queue<Job> qu, int cap) {
        this.queue = qu;
        this.cap = cap;
        lock = new ReentrantLock();
        notEmpty = lock.newCondition();
        notFull = lock.newCondition();
    }

    public void produceJob(Job jb)
        throws InterruptedException{
        lock.lock();
        try {
            while(queue.size() >= cap){
                System.err.println("Producer waiting...");
                notFull.await();
            }
            queue.add(jb);
            notEmpty.signal();
        } finally {
            lock.unlock();
        }
    }
    public void consumeJob()
        throws InterruptedException{
        lock.lock();
        try {
            while(queue.isEmpty()){
                System.out.println("Consumer waiting...");
                notEmpty.await();
            }
            Job cj = queue.poll();
            System.out.println("Consumer consuming " + cj.id);
            notFull.signal();
        } finally {
            lock.unlock();
        }
    }
}

public class ProdConsDemo {

    public static void main(String[] args) {
        Queue<Job> jbq = new ArrayDeque<>(3);
        
        JobQueue jobQueue =
                new JobQueue(jbq, 3);

        Thread producer = new Thread(() -> {

            int count = 1;

            try {

                while (true) {

                    Job job =
                            new Job("JOB-" + count++);

                    System.out.println(
                            Thread.currentThread().getName()
                            + " Producing "
                            + job.id);

                    jobQueue.produceJob(job);

                    Thread.sleep(1000);

                }

            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        });

        Thread consumer1 = new Thread(() -> {

            try {

                while (true) {

                    jobQueue.consumeJob();

                    Thread.sleep(2000);

                }

            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        });

        Thread consumer2 = new Thread(() -> {

            try {

                while (true) {

                    jobQueue.consumeJob();

                    Thread.sleep(3000);

                }

            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        });

        producer.setName("Producer");

        consumer1.setName("Consumer-1");

        consumer2.setName("Consumer-2");

        producer.start();

        consumer1.start();

        consumer2.start();
    }
}
