#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <opencv2/opencv.hpp>

int main()
{
    // Read image data into memory using OpenCV.
    printf("Reading image into memory...\n");
    cv::Mat mat = cv::imread("person.jpg");
    size_t size = mat.rows * mat.step;

    // Setup shared memory.
    printf("Setting up shared memory...\n");
    int shmid = shmget(123456, size, IPC_CREAT | 0666);
    if (!shmid) {
        printf("Error getting shared memory id");
        exit(1);
    }
    void *shared_memory = shmat(shmid, NULL, 0);
    if (!shared_memory) {
        printf("Error attaching shared memory id");
        exit(1);
    }

    // Copy image data to shared memory.
    printf("Copying image from mat into shared memory...\n");
    memcpy(shared_memory, mat.data, size);
    sleep(10);

    // Detach and remove shared memory
    printf("Detaching and removing shared memory...\n");
    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, NULL);

    printf("Done.\n");
}
