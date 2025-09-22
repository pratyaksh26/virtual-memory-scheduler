#pragma once

// Represents all metadata for a single job.
struct ProcessControlBlock {
    int jobId;
    int timeLimit;      // Total Time Limit (TTL)
    int lineLimit;      // Total Line Limit (TLL)
    int timeCounter = 0;    // Time Used
    int lineCounter = 0;    // Lines Printed

    ProcessControlBlock(int id, int tl, int ll)
        : jobId(id), timeLimit(tl), lineLimit(ll) {}
};