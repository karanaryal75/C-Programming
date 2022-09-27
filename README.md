# Create a database clone

Create a database clone in the RDS console. A link to the database identifier can be found in the CloudFormation console
by searching for 'DatabaseCluster' in the resources tab of the Orion RDS stack.

Click the link for DatabaseCluster. Once inside the RDS Console, note down the following values.

    * Database Cluster Arn
    * Existing Security Group
    * VPC

Database Cluster Arn, Existing Security Group and VPC can be found once you click the writer instance under Connectivity & Security tab. 
Leave the KmsKeyId parameter blank when performing same-account cloning.\
For cross-account cloning refer to [Cross-account cloning](#cross-account-cloning).

Create the postgres_clone stack with the following command.

    cid -p AWS_PROFILE postgres-clone create -s STACK_NAME

    CloudFormation Parameters:
    * ExisitingSecurityGroup: EXISTING-SECURITY-GROUP-FROM-ABOVE
    * KmsKeyId: FOR-CROSS-ACCOUNT-CLONING-ONLY
    * SourceClusterArn: DATABASE-CLUSTER_ARN-FROM-ABOVE
    * VPCID: VPC-ID-FROM-ABOVE 

After approximately 10 minutes, you can find the newly created postgres-clone stack in CloudFormation with the name you
entered as 'STACK_NAME' when performing the cid command above. 

### Accessing the clone

After the postgres_clone stack is created in CloudFormation; Under Output tab you can find the id for the clone cluster. 
On the RDS Console search for clone cluster id. Note down its endpoints to connect to the database. 

### Hook a clone to an Orion stack

Log into the `postgres-clone` database and run the following command with the clone's endpoint noted from above.

    psql postgres -h CLONE-ENDPOINT -U USERNAME

Once inside the database, rename one of the available databases. Let's say `database_name` to `ORION_STACK_NAME` 
by running the postgres command below.

**Note**: postgres does not accept hyphens, so you have to substitute hyphens with underscores. 
For example: `orion-customer-prod` would become `orion_customer_prod`.

    alter database "database_name" rename to "ORION_STACK_NAME";

After renaming, update the orion stack using the command below and update the `DatabaseStackName` parameter 
to your `postgres-clone-stack` name.

    cid -p AWS_PROFILE orion update -s ORION_STACK_NAME

Once the update is complete, the clone is successfully hooked to an orion stack. 

### Deleting a clone stack

Once you are done using the clone, enter the command below to delete the clone and its underlying resources.

    cid -p AWS_PROFILE postgres-clone delete -s STACK_NAME

## Cross-account cloning

To perform cross-account cloning, first log into the account where the cluster is present to share it to the desired
account in which you wish to clone. Once inside that account's RDS console page, click the cluster.\

`Note down the value of Cluster Arn.`

Under configuration tab, click the AWS KMS Key link present under Encryption heading. After you are into the KMS 
Customer-managed key page, you will notice Key policy.

`Update the key policy and note down the value of KmsKey Arn.`

```
    For example: We want to clone a cluster present in a account1 (AccountId: XXXXXXXXXX12) from 
    account2 (AccountId: XXXXXXXXXX22). In the account1 the cluster's kms policy will be
    
    {
        "Version": "2012-10-17",
        "Statement": [
            {
                "Effect": "Allow",
                "Principal": {
                    "AWS": "arn:aws:iam::XXXXXXXXXX12:root"
                },
                "Action": "kms:*",
                "Resource": "*"
            }
        ]
    }
    
    Update the policy giving access to the account2. Hence, the updated policy becomes:
    
    {
        "Version": "2012-10-17",
        "Statement": [
            {
                "Effect": "Allow",
                "Principal": {
                    "AWS": "arn:aws:iam::XXXXXXXXXX12:root"
                },
                "Action": "kms:*",
                "Resource": "*"
            },
            {
                "Effect": "Allow",
                "Principal": {
                    "AWS": "arn:aws:iam::XXXXXXXXXX22:root"
                },
                "Action": "kms:*",
                "Resource": "*"
            }
        ]
    }
```

After the kms policy is updated, we share the cluster via AWS Resource Access Manager(RAM).\

Navigate to RAM console and follow the steps below:

    Navigate to Shared by me tab -> Resource Shares.   
    Create resource share -> resource share name -> resource type (Aurora DB Clusters)
    Select available db cluster you wish to share from the list and its underlying resource id
    Associate permission: This step is auto populated, so proceed to Next
    Grant access to principal -> add account id -> select principal
    Review and create resource share

Once the resource is shared, navigate to the target account. On the rds console now you can see a db cluster shared 
from the host account, the description tab shows which account shared the cluster. 

Now to operate cross-account cloning run the following command below.

    cid -p <AWS_PROFILE> postgres-clone create -s <STACK_NAME>

    CloudFormation Parameters:
    SourceClusterArn: CLUSTER-ARN-SHARED-FROM-DIFFERENT-ACCOUNT
    KmsKeyId: KMS-KEY-ID-OF-SHARED-CLUSTER

#### Limitations of cross-account cloning

Please refer to the following link to learn about the limitation of cross-account cloning.\
https://docs.aws.amazon.com/AmazonRDS/latest/AuroraUserGuide/Aurora.Managing.Clone.html#:~:text=another%20AWS%20account-,Limitations%20of%20cross%2Daccount%20cloning,-Aurora%20cross%2Daccount
