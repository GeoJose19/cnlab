#include<stdio.h>

void main() {
    int in, out, bsize, n, bucket = 0;
    
    // Input bucket size, outgoing rate, and number of inputs
    printf("Enter the bucket size : ");
    scanf("%d", &bsize);
    
    printf("Enter the number of inputs: ");
    scanf("%d", &n);
    
    printf("Enter the packet outgoing rate : ");
    scanf("%d", &out);
    
    // Process each incoming packet
    while (n != 0) {
        printf("\nEnter the incoming packet size : ");
        scanf("%d", &in);
        printf("Incoming packet size : %d\n", in);
        
        // Check if incoming packet can be accommodated in the bucket
        if (in <= (bsize - bucket)) {
            bucket += in;
            printf("Bucket status : %d out of %d\n", bucket, bsize);
        } else {
            printf("Dropped packets : %d\n", in - (bsize - bucket));
            printf("Bucket status : %d out of %d\n", bucket, bsize);
            bucket = bsize;  // Set bucket to full capacity after dropping packets
        }
        
        // Simulate outgoing packets from the bucket
        bucket -= out;
        printf("After outgoing, bucket status : %d packets out of %d\n", bucket, bsize);
        
        n--;  // Decrement the number of inputs
    }
}

