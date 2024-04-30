#include <stdio.h>

int main() {
    int incoming, outgoing, bucket_size, n, storage = 0;
    printf("Enter the Bucket size, Outgoing rate and Number of input : ");
    scanf("%d %d %d", &bucket_size, &outgoing, &n);

    while(n != 0) {
        printf("\nEnter the Incoming packet size : ");
        scanf("%d", &incoming);
        printf("Incoming packet size : %d\n", incoming);

        if(incoming <= (bucket_size - storage)) {
            storage += incoming;
            printf("Bucket buffer size : %d out of %d\n", storage, bucket_size);
        } else {
            printf("Dropped %d packets\n", incoming - (bucket_size - storage));
            storage = bucket_size;
            printf("Bucket buffer size : %d out of %d\n", storage, bucket_size);
        }

        storage = storage - outgoing;

        printf("After Outgoing, Bucket buffer size : %d out of %d\n", storage, bucket_size);
        n--;
    }
}

/*
Enter the Bucket size, Outgoing rate and Number of input : 1000 100 5

Enter the Incoming packet size : 100
Incoming packet size : 100
Bucket buffer size : 100 out of 1000
After Outgoing, Bucket buffer size : 0 out of 1000

Enter the Incoming packet size : 200
Incoming packet size : 200
Bucket buffer size : 200 out of 1000
After Outgoing, Bucket buffer size : 100 out of 1000

Enter the Incoming packet size : 300
Incoming packet size : 300
Bucket buffer size : 400 out of 1000
After Outgoing, Bucket buffer size : 300 out of 1000

Enter the Incoming packet size : 400
Incoming packet size : 400
Bucket buffer size : 700 out of 1000
After Outgoing, Bucket buffer size : 600 out of 1000

Enter the Incoming packet size : 500
Incoming packet size : 500
Dropped 100 packets
Bucket buffer size : 1000 out of 1000
After Outgoing, Bucket buffer size : 900 out of 1000
*/
