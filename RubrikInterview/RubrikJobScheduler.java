import java.util.*;
import java.util.concurrent.locks.*;

public class RubrikJobScheduler {
    // Defines a job inside the system
    static class Job implements Comparable<Job> {
        String jobId;
        String userId;
        long scheduledTime; // Epoch timestamp in milliseconds

        public Job(String jobId, String userId, long scheduledTime) {
            this.jobId = jobId;
            this.userId = userId;
            this.scheduledTime = scheduledTime;
        }

        @Override
        public int compareTo(Job other) {
            return Long.compare(this.scheduledTime, other.scheduledTime);
        }
    }

    private final PriorityQueue<Job> jobQueue = new PriorityQueue<>();
    private final ReentrantLock lock = new ReentrantLock();
    private final Condition settingsChanged = lock.newCondition();
    
    // Tracks user execution history for rate limiting: UserId -> List of execution timestamps
    private final Map<String, List<Long>> userHistory = new HashMap<>();
    private final int MAX_JOBS_PER_SEC = 2; // Rate limit threshold
    private final boolean isRunning = true;

    public RubrikJobScheduler() {
        // Start the background execution engine
        Thread worker = new Thread(this::runExecutionLoop);
        worker.setDaemon(true);
        worker.start();
    }

    // Thread-safe method to submit jobs
    public void scheduleJob(String jobId, String userId, long TargetExecutionTime) {
        lock.lock();
        try {
            long finalScheduledTime = calculateRateLimitedTime(userId, TargetExecutionTime);
            Job newJob = new Job(jobId, userId, finalScheduledTime);
            jobQueue.add(newJob);
            
            // Log user execution intent to lock their rate-limiting slot
            userHistory.computeIfAbsent(userId, k -> new ArrayList<>()).add(finalScheduledTime);
            
            // Signal worker thread in case this new job needs to run earlier than previous head
            settingsChanged.signalAll();
            System.out.println("Job " + jobId + " scheduled for user " + userId + " at " + finalScheduledTime);
        } finally {
            lock.unlock();
        }
    }

    // Evaluates rate limits and shifts the execution time forward if necessary
    private long calculateRateLimitedTime(String userId, long proposedTime) {
        List<Long> history = userHistory.get(userId);
        if (history == null || history.isEmpty()) return proposedTime;

        long actualTime = proposedTime;
        while (true) {
            int count = 0;
            long windowStart = actualTime - 1000; // 1 second window
            
            for (long time : history) {
                if (time >= windowStart && time <= actualTime) {
                    count++;
                }
            }

            if (count < MAX_JOBS_PER_SEC) {
                return actualTime;
            }
            // Push time forward by 100ms to look for next available slot
            actualTime += 100; 
        }
    }

    // Infinite loop executing jobs when their time comes
    private void runExecutionLoop() {
        while (isRunning) {
            lock.lock();
            try {
                while (jobQueue.isEmpty()) {
                    settingsChanged.await(); // Sleep until a job arrives
                }

                long currentTime = System.currentTimeMillis();
                Job nextJob = jobQueue.peek();

                if (currentTime >= nextJob.scheduledTime) {
                    jobQueue.poll();
                    execute(nextJob);
                } else {
                    // Sleep until the exact time the next job is ready
                    long sleepTime = nextJob.scheduledTime - currentTime;
                    settingsChanged.awaitNanos(sleepTime * 1_000_000L);
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                break;
            } finally {
                lock.unlock();
            }
        }
    }

    private void execute(Job job) {
        System.out.println(">>> EXECUTING: Job " + job.jobId + " for User " + job.userId + " at " + System.currentTimeMillis());
    }
}
