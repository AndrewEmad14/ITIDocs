# AWS Cloud Practitioner exam - CLF-C02

covers 40 AWS services 

data center ,bunch of servers in a place


Problems with traditional IT approach

    Pay for the rent for the data center

    Pay for power supply, cooling, maintenance

    Adding and replacing hardware takes time

    Scaling is limited

    Hire 24/7 team to monitor the infrastructure

    How to deal with disasters? (earthquake, power shutdown, fire...)

What is Cloud Computing?

    Cloud computing is the on-demand delivery of compute power, database storage, applications, and other IT resources

    Through a cloud services platform with pay-as-you-go pricing

    You can provision exactly the right type and size of computing resources you need

    You can access as many resources as you need, almost instantly

    Simple way to access servers, storage, databases and a set of application services

    Amazon Web Services owns and maintains the network-connected hardware required for these application services, while you provision and use what you need via a web application.

The Deployment Models of the Cloud
Private Cloud

    Cloud services used by a single organization, not exposed to the public.

    Complete control

    Security for sensitive applications

    Meet specific business needs
  example : rackspace
Public Cloud

    Cloud resources owned and operated by a third-party cloud service provider delivered over the Internet.

    Six Advantages of Cloud Computing
  example : aws ,azure, google cloud
Hybrid Cloud

    Keep some servers on premises and extend some capabilities to the Cloud
    control over senstive data
    flexability of the public cloud 

  The Five Characteristics of Cloud Computing

    On-demand self service:

        Users can provision resources and use them without human interaction from the service provider

    Broad network access:

        Resources available over the network, and can be accessed by diverse client platforms

    Multi-tenancy and resource pooling:

        Multiple customers can share the same infrastructure and applications with security and privacy

        Multiple customers are serviced from the same physical resources

    Rapid elasticity and scalability:

        Automatically and quickly acquire and dispose resources when needed

        Quickly and easily scale based on demand

    Measured service:

        Usage is measured, users pay correctly for what they have used

## Six Advantages of Cloud Computing

* Trade capital expense (CAPEX) for operational expense (OPEX)
    * Pay On-Demand: don't own hardware
    * Reduced Total Cost of Ownership (TCO) & Operational Expense (OPEX)
* Benefit from massive economies of scale
    * Prices are reduced as AWS is more efficient due to large scale
* Stop guessing capacity
    * Scale based on actual measured usage
* Increase speed and agility
* Stop spending money running and maintaining data centers
* Go global in minutes: leverage the AWS global infrastructure

## Problems solved by the Cloud

* Flexibility: change resource types when needed
* Cost-Effectiveness: pay as you go, for what you use
* Scalability: accommodate larger loads by making hardware stronger or adding additional nodes
* Elasticity: ability to scale out and scale-in when needed
* High-availability and fault-tolerance: build across data centers
* Agility: rapidly develop, test and launch software applications


## Types of Cloud Computing

* **Infrastructure as a Service (IaaS)**
    * Provide building blocks for cloud IT
    * Provides networking, computers, data storage space
    * Highest level of flexibility
    * Easy parallel with traditional on-premises IT
* **Platform as a Service (PaaS)**
    * Removes the need for your organization to manage the underlying infrastructure
    * Focus on the deployment and management of your applications
* **Software as a Service (SaaS)**
    * Completed product that is run and managed by the service provider


## Pricing of the Cloud – Quick Overview

* AWS has 3 pricing fundamentals, following the pay-as-you-go pricing model
* Compute:
    * Pay for compute time
* Storage:
    * Pay for data stored in the Cloud
* Data transfer OUT of the Cloud:
    * Data transfer IN is free
* Solves the expensive issue of traditional IT

## How to choose an AWS Region?

If you need to launch a new application, where should you do it?

* **Compliance** with data governance and legal requirements: data never leaves a region without your explicit permission
* **Proximity** to customers: reduced latency
* **Available services** within a Region: new services and new features aren't available in every Region
* **Pricing:** pricing varies region to region and is transparent in the service pricing page

## AWS Availability Zones

* Each region has many availability zones (usually 3, min is 3, max is 6). Example:
    * ap-southeast-2a
    * ap-southeast-2b
    * ap-southeast-2c
* Each availability zone (AZ) is one or more discrete data centers with redundant power, networking, and connectivity
* They're separate from each other, so that they're isolated from disasters
* They're connected with high bandwidth, ultra-low latency networking

## Tour of the AWS Console

* AWS has Global Services:
    * Identity and Access Management (IAM)
    * Route 53 (DNS service)
    * CloudFront (Content Delivery Network)
    * WAF (Web Application Firewall)
* Most AWS services are Region-scoped:
    * Amazon EC2 (Infrastructure as a Service)
    * Elastic Beanstalk (Platform as a Service)
    * Lambda (Function as a Service)
    * Rekognition (Software as a Service)

AWS Acceptable Use Policy

    https://aws.amazon.com/aup/

    No Illegal, Harmful, or Offensive Use or Content

    No Security Violations

    No Network Abuse

    No E-Mail or Other Message Abuse

## IAM: Users & Groups

* **IAM = Identity and Access Management, Global service**
* **Root account** created by default, shouldn't be used or shared
* **Users** are people within your organization, and can be grouped
* **Groups** only contain users, not other groups
* **Users** don't have to belong to a group, and user can belong to multiple groups

give the user the exact privlage he needs , nothing more


IAM Policies Structure

    Consists of

        Version: policy language version, always include "2012-10-17"

        Id: an identifier for the policy (optional)

        Statement: one or more individual statements (required)

    Statements consists of

        Sid: an identifier for the statement (optional)

        Effect: whether the statement allows or denies access (Allow, Deny)

        Principal: account/user/role to which this policy applied to

        Action: list of actions this policy allows or denies

        Resource: list of resources to which the actions applied to

        Condition: conditions for when this policy is in effect (optional)

IAM – Password Policy

    Strong passwords = higher security for your account

    In AWS, you can setup a password policy:

        Set a minimum password length

        Require specific character types:

            including uppercase letters

            lowercase letters

            numbers

            non-alphanumeric characters

        Allow all IAM users to change their own passwords

        Require users to change their password after some time (password expiration)

        Prevent password re-use


Multi Factor Authentication - MFA

    Users have access to your account and can possibly change configurations or delete resources in your AWS account

    You want to protect your Root Accounts and IAM users

    MFA = password you know + security device you own

    Main benefit of MFA: if a password is stolen or hacked, the account is not compromised


MFA options 
  virtual mfa
  universal 2nd factor security key
  hardaware  key fob mfa
  aws govcloud hardware key fob

## How can users access AWS?

* To access AWS, you have three options:
    * AWS Management Console (protected by password + MFA)
    * AWS Command Line Interface (CLI): protected by access keys
    * AWS Software Developer Kit (SDK) - for code: protected by access keys
* Access Keys are generated through the AWS Console
* Users manage their own access keys
* **Access Keys are secret, just like a password. Don't share them**
* Access Key ID ~= username
* Secret Access Key ~= password

IAM Security Tools

    IAM Credentials Report (account-level)

        a report that lists all your account's users and the status of their various credentials

    IAM Access Advisor (user-level)

        Access advisor shows the service permissions granted to a user and when those services were last accessed.

# IAM Guidelines & Best Practices

* Don't use the root account except for AWS account setup
* One physical user = One AWS user
* Assign users to groups and assign permissions to groups
* Create a strong password policy
* Use and enforce the use of Multi Factor Authentication (MFA)
* Create and use Roles for giving permissions to AWS services
* Use Access Keys for Programmatic Access (CLI / SDK)
* Audit permissions of your account using IAM Credentials Report & IAM Access Advisor
* **Never share IAM users & Access Keys**


# Shared Responsibility Model for IAM

### AWS
* Infrastructure (global network security)
* Configuration and vulnerability analysis
* Compliance validation

### You
* Users, Groups, Roles, Policies management and monitoring
* Enable MFA on all accounts
* Rotate all your keys often
* Use IAM tools to apply appropriate permissions
Which of the following is an IAM Security Tool?

    IAM Credentials Report (Correct)

        IAM Credentials report lists all your account's users and the status of their various credentials. The other IAM Security Tool is IAM Access Advisor. It shows the service permissions granted to a user and when those services were last accessed.

go to bills to know what the specific of the cost

budget will notify you if you are going to exceed it


The text from the image has been extracted and formatted below:
Amazon EC2

    EC2 is one of the most popular of AWS’ offering

    EC2 = Elastic Compute Cloud = Infrastructure as a Service

    It mainly consists in the capability of:

        Renting virtual machines (EC2)

        Storing data on virtual drives (EBS)

        Distributing load across machines (ELB)

        Scaling the services using an auto-scaling group (ASG)

    Knowing EC2 is fundamental to understand how the Cloud works

EC2 sizing & configuration options

    Operating System (OS): Linux, Windows or Mac OS

    How much compute power & cores (CPU)

    How much random-access memory (RAM)

    How much storage space:

        Network-attached (EBS & EFS)

        hardware (EC2 Instance Store)

    Network card: speed of the card, Public IP address

    Firewall rules: security group

    Bootstrap script (configure at first launch): EC2 User Data


EC2 User Data

* It is possible to bootstrap our instances using an EC2 User data script.
* bootstrapping means launching commands when a machine starts
* That script is only run once at the instance first start
* EC2 user data is used to automate boot tasks such as:
    * Installing updates
    * Installing software
    * Downloading common files from the internet
    * Anything you can think of
* The EC2 User Data Script runs with the root user


if you stop and instance then start it again it will have a different ip address

## EC2 Instance Types - Overview

* You can use different types of EC2 instances that are optimised for different use cases ([https://aws.amazon.com/ec2/instance-types/](https://aws.amazon.com/ec2/instance-types/))
* AWS has the following naming convention:

### **m5.2xlarge**

* **m**: instance class
* **5**: generation (AWS improves them over time)

---

**Use Case Categories:**
* General Purpose
* Compute Optimized
* Memory Optimized
* Accelerated Computing
* Storage Optimized
* HPC Optimized
* Instance Features
* Measuring Instance Performance


## EC2 Instance Types – General Purpose

* Great for a diversity of workloads such as web servers or code repositories
* Balance between:
    * Compute
    * Memory
    * Networking
* In the course, we will be using the t2.micro which is a General Purpose EC2 instance

## EC2 Instance Types – Compute Optimized

* Great for compute-intensive tasks that require high performance processors:
    * Batch processing workloads
    * Media transcoding
    * High performance web servers
    * High performance computing (HPC)
    * Scientific modeling & machine learning
    * Dedicated gaming servers

---

**Compute Optimized**

Compute Optimized instances are ideal for compute bound applications that benefit from high performance processors. Instances belonging to this family are well suited for batch processing workloads, media transcoding, high performance web servers, high performance computing (HPC), scientific modeling, dedicated gaming servers and ad server engines, machine learning inference and other compute intensive applications.

**Instance Families:**
**C6g** | C6gn | C5 | C5a | C5n | C4

## EC2 Instance Types – Memory Optimized

* Fast performance for workloads that process large data sets in memory
* Use cases:
    * High performance, relational/non-relational databases
    * Distributed web scale cache stores
    * In-memory databases optimized for BI (business intelligence)
    * Applications performing real-time processing of big unstructured data

---

**Memory Optimized**

Memory optimized instances are designed to deliver fast performance for workloads that process large data sets in memory.

**Instance Families:**
**R6g** | R5 | R5a | R5b | R5n | R4 | X1e | X1 | High Memory | z1d

## EC2 Instance Types – Storage Optimized

* Great for storage-intensive tasks that require high, sequential read and write access to large data sets on local storage
* Use cases:
    * High frequency online transaction processing (OLTP) systems
    * Relational & NoSQL databases
    * Cache for in-memory databases (for example, Redis)
    * Data warehousing applications
    * Distributed file systems

---

**Storage Optimized**

Storage optimized instances are designed for workloads that require high, sequential read and write access to very large data sets on local storage. They are optimized to deliver tens of thousands of low-latency, random I/O operations per second (IOPS) to applications.

**Instance Families:**
**I3** | I3en | D2 | D3 | D3en | H1

## Introduction to Security Groups

* Security Groups are the fundamental of network security in AWS
* They control how traffic is allowed into or out of our EC2 Instances.

**Visual Diagram Description:**
[ WWW ] --- Inbound traffic ---> [ Security Group | EC2 Instance ]

* Security groups only contain **allow** rules
* Security groups rules can reference by IP or by security group

---

## Security Groups Deeper Dive

* Security groups are acting as a “firewall” on EC2 instances
* They regulate:
    * Access to Ports
    * Authorised IP ranges – IPv4 and IPv6
    * Control of inbound network (from other to the instance)
    * Control of outbound network (from the instance to other)

---

| Type | Protocol | Port Range | Source | Description |
| :--- | :--- | :--- | :--- | :--- |
| HTTP | TCP | 80 | 0.0.0.0/0 | test http page |
| SSH | TCP | 22 | 122.149.196.85/32 | |
| Custom TCP Rule | TCP | 4567 | 0.0.0.0/0 | java app |

Security Groups
Good to know

    Can be attached to multiple instances

    Locked down to a region / VPC combination

    Does live "outside" the EC2 – if traffic is blocked the EC2 instance won't see it

    It's good to maintain one separate security group for SSH access

    If your application is not accessible (time out), then it's a security group issue

    If your application gives a "connection refused" error, then it's an application error or it's not launched

    All inbound traffic is blocked by default

Amazon EC2

    EC2 is one of the most popular of AWS’ offering

    EC2 = Elastic Compute Cloud = Infrastructure as a Service

    It mainly consists in the capability of :

        Renting virtual machines (EC2)

        Storing data on virtual drives (EBS)

        Distributing load across machines (ELB)

        Scaling the services using an auto-scaling group (ASG)

    Knowing EC2 is fundamental to understand how the Cloud works

Classic Ports to know

    22 = SSH (Secure Shell) - log into a Linux instance

    21 = FTP (File Transfer Protocol) – upload files into a file share

    22 = SFTP (Secure File Transfer Protocol) – upload files using SSH

    80 = HTTP – access unsecured websites

    443 = HTTPS – access secured websites

    3389 = RDP (Remote Desktop Protocol) – log into a Windows instance

ways to connect to ec2 
    putty
    ssh
    ec2 instace connect


## EC2 Instances Purchasing Options

* On-Demand Instances – short workload, predictable pricing, pay by second
* Reserved (1 & 3 years)
    * Reserved Instances – long workloads
    * Convertible Reserved Instances – long workloads with flexible instances
* Savings Plans (1 & 3 years) – commitment to an amount of usage, long workload
* Spot Instances – short workloads, cheap, can lose instances (less reliable)
* Dedicated Hosts – book an entire physical server, control instance placement
* Dedicated Instances – no other customers will share your hardware
* Capacity Reservations – reserve capacity in a specific AZ for any duration

EC2 On Demand

    Pay for what you use:

        Linux or Windows - billing per second, after the first minute

        All other operating systems - billing per hour

    Has the highest cost but no upfront payment

    No long-term commitment

    Recommended for short-term and un-interrupted workloads, where you can't predict how the application will behave

EC2 Reserved Instances

• Up to 72% discount compared to On-demand
• You reserve a specific instance attributes (Instance Type, Region, Tenancy, OS)
• Reservation Period – 1 year (+discount) or 3 years (+++discount)
• Payment Options – No Upfront (+), Partial Upfront (++), All Upfront (+++)
• Reserved Instance's Scope – Regional or Zonal (reserve capacity in an AZ)
• Recommended for steady-state usage applications (think database)
• You can buy and sell in the Reserved Instance Marketplace

• Convertible Reserved Instance
  • Can change the EC2 instance type, instance family, OS, scope and tenancy
  • Up to 66% discount

Note: the % discounts are different from the video as AWS change them over time – the exact numbers are not needed for the exam. This is just for illustrative purposes 


EC2 Dedicated Hosts

• A physical server with EC2 instance capacity fully dedicated to your use
• Allows you address compliance requirements and use your existing server-bound software licenses (per-socket, per-core, pe—VM software licenses)
• Purchasing Options:
  • On-demand – pay per second for active Dedicated Host
  • Reserved - 1 or 3 years (No Upfront, Partial Upfront, All Upfront)
• The most expensive option

• Useful for software that have complicated licensing model (BYOL – Bring Your Own License)
• Or for companies that have strong regulatory or compliance needs


EC2 Dedicated Instances

• Instances run on hardware that's dedicated to you

• May share hardware with other instances in same account

• No control over instance placement (can move hardware after Stop / Start)

EC2 Capacity Reservations

• Reserve On-Demand instances capacity in a specific AZ for any duration
• You always have access to EC2 capacity when you need it
• No time commitment (create/cancel anytime), no billing discounts
• Combine with Regional Reserved Instances and Savings Plans to benefit from billing discounts
• You're charged at On-Demand rate whether you run instances or not

• Suitable for short-term, uninterrupted workloads that needs to be in a specific AZ



Which purchasing option is right for me?

• On demand: coming and staying in resort whenever we like, we pay the full price
• Reserved: like planning ahead and if we plan to stay for a long time, we may get a good discount.
• Savings Plans: pay a certain amount per hour for certain period and stay in any room type (e.g., King, Suite, Sea View, …)
• Spot instances: the hotel allows people to bid for the empty rooms and the highest bidder keeps the rooms. You can get kicked out at any time
• Dedicated Hosts: We book an entire building of the resort
• Capacity Reservations: you book a room for a period with full price even you don't stay in it


Shared Responsibility Model for EC2

AWS:
• Infrastructure (global network security)
• Isolation on physical hosts
• Replacing faulty hardware
• Compliance validation

User:
• Security Groups rules
• Operating-system patches and updates
• Software and utilities installed on the EC2 instance
• IAM Roles assigned to EC2 & IAM user access management
• Data security on your instance


EC2 Section – Summary

• EC2 Instance: AMI (OS) + Instance Size (CPU + RAM) + Storage + security groups + EC2 User Data
• Security Groups: Firewall attached to the EC2 instance
• EC2 User Data: Script launched at the first start of an instance
• SSH: start a terminal into our EC2 Instances (port 22)
• EC2 Instance Role: link to IAM roles
• Purchasing Options: On-Demand, Spot, Reserved (Standard + Convertible), Dedicated Host, Dedicated Instance

What's an EBS Volume?

• An EBS (Elastic Block Store) Volume is a network drive you can attach to your instances while they run
• It allows your instances to persist data, even after their termination
• They can only be mounted to one instance at a time (at the CCP level)
• They are bound to a specific availability zone

• Analogy: Think of them as a "network USB stick"


EBS Volume

• It's a network drive (i.e. not a physical drive)
  • It uses the network to communicate the instance, which means there might be a bit of latency
  • It can be detached from an EC2 instance and attached to another one quickly

• It's locked to an Availability Zone (AZ)
  • An EBS Volume in us-east-1a cannot be attached to us-east-1b
  • To move a volume across, you first need to snapshot it

• Have a provisioned capacity (size in GBs, and IOPS)
  • You get billed for all the provisioned capacity
  • You can increase the capacity of the drive over time


  you can have the delete on termination option in ec2


  EBS Snapshots Features

• EBS Snapshot Archive
  • Move a Snapshot to an "archive tier" that is 75% cheaper
  • Takes within 24 to 72 hours for restoring the archive

• Recycle Bin for EBS Snapshots
  • Setup rules to retain deleted snapshots so you can recover them after an accidental deletion
  • Specify retention (from 1 day to 1 year)

AMI Overview

• AMI = Amazon Machine Image
• AMI are a customization of an EC2 instance
  • You add your own software, configuration, operating system, monitoring…
  • Faster boot / configuration time because all your software is pre-packaged
• AMI are built for a specific region (and can be copied across regions)
• You can launch EC2 instances from:
  • A Public AMI: AWS provided
  • Your own AMI: you make and maintain them yourself
  • An AWS Marketplace AMI: an AMI someone else made (and potentially sells)

## AMI vs User Data in EC2

These are two different mechanisms for configuring EC2 instances, operating at different stages of the instance lifecycle.

---

### AMI (Amazon Machine Image)

An AMI is a **pre-baked snapshot** used to launch an instance. It contains:

- The **operating system** (e.g., Amazon Linux, Ubuntu, Windows)
- **Pre-installed software** and packages
- **Configuration files** baked in at image creation time
- The **root volume** and optionally additional EBS volume snapshots
- Launch permissions and block device mappings

Think of it as a **golden template** — every instance launched from the same AMI starts identical. You can use AWS-provided AMIs, Marketplace AMIs, or create your own custom AMI from an existing instance.

**When to use:** When you want a fully configured, reusable base image that takes a long time to set up (e.g., pre-installed app server, custom security hardening).

---

### User Data

User Data is a **startup script** that runs **once** when an instance first boots (by default). It's a shell script or cloud-init directive passed at launch time.

- Runs as **root** automatically on first boot
- Used for dynamic configuration (e.g., pulling latest code, setting env variables, registering with a service)
- Can install packages, start services, write files, etc.
- Not baked into the image — it's injected per-launch

**When to use:** For lightweight, dynamic setup tasks that differ between environments (dev/prod) or need to happen at launch time with fresh data.

---

### Key Differences

| | AMI | User Data |
|---|---|---|
| **What it is** | Full machine image snapshot | Boot-time script |
| **When it runs** | At instance creation | On first boot (or every boot) |
| **Speed** | Fast boot (pre-configured) | Slower (runs setup on launch) |
| **Reusability** | High — shared across many launches | Per-launch, can vary |
| **Mutability** | Immutable once created | Dynamic, environment-specific |
| **Size** | GBs (full disk snapshot) | Max 16 KB |
| **Use case** | Baked-in software & OS config | Dynamic config, secrets, registration |

---

### How They Work Together

A common pattern is to combine both:

1. **AMI** — has the OS + your app's dependencies pre-installed (fast boot, no package downloads)
2. **User Data** — pulls the latest app version, injects environment-specific config, starts the service

This gives you the **speed of a pre-baked image** with the **flexibility of dynamic configuration** at launch.

Yes, technically you **can** do everything in User Data — but you generally **shouldn't**. Here's why:

---

### What you'd be doing

```bash
#!/bin/bash
apt-get update
apt-get install -y nginx python3 postgresql-client ...
git clone https://github.com/your/app.git
pip install -r requirements.txt
# ... 500 more lines
```

This works, but it comes with real costs.

---

### The problems

**Boot time** is the biggest one. Every instance launch has to repeat all that work — downloading packages, compiling, installing. What takes 30 seconds with a baked AMI might take 10–20 minutes in User Data. In an Auto Scaling event where you need 10 new instances fast, that delay hurts badly.

**Reliability on external dependencies.** Your script pulls from apt, pip, GitHub, etc. If any of those are slow or down at launch time, your instance fails to configure properly. An AMI has no such dependency — everything is already on disk.

**Cost.** You're paying for EC2 time while the instance sits there installing things before it can serve traffic.

**Reproducibility.** Running the same User Data script a week later might produce a slightly different result — a package updated, a repo changed, a URL moved. An AMI is frozen in time and always identical.

---

### So when is User Data alone fine?

- **Simple, fast scripts** — a few env vars, one service restart, register with a load balancer
- **Prototyping / dev environments** where boot time doesn't matter
- **Infrequently launched instances** that aren't in an Auto Scaling group

---

### The mental model

Think of it like a Docker image vs its entrypoint command. You wouldn't install Node.js in the entrypoint every time the container starts — you bake it into the image. The entrypoint just does the dynamic stuff at runtime.

AMI = the image. User Data = the entrypoint.

AMI Process (from an EC2 instance)

• Start an EC2 instance and customize it
• Stop the instance (for data integrity)
• Build an AMI – this will also create EBS snapshots
• Launch instances from other AMIs

EC2 Image Builder
Used to automate the creation of Virtual Machines or container images
=> Automate the creation, maintain, validate and test EC2 AMIs
its a free service
can run on a schedule

EC2 Instance Store

• EBS volumes are network drives with good but "limited" performance
• If you need a high-performance hardware disk, use EC2 Instance Store

• Better I/O performance
• EC2 Instance Store lose their storage if they're stopped (ephemeral)
• Good for buffer / cache / scratch data / temporary content
• Risk of data loss if hardware fails
• Backups and Replication are your responsibility

EFS – Elastic File System

• Managed NFS (network file system) that can be mounted on 100s of EC2
• EFS works with Linux EC2 instances in multi-AZ
• Highly available, scalable, expensive (3x gp2), pay per use, no capacity planning


EFS Infrequent Access (EFS-IA)

• Storage class that is cost-optimized for files not accessed every day
• Up to 92% lower cost compared to EFS Standard
• EFS will automatically move your files to EFS-IA based on the last time they were accessed
• Enable EFS-IA with a Lifecycle Policy
• Example: move files that are not accessed for 60 days to EFS-IA
• Transparent to the applications accessing EFS

Shared Responsibility Model for EC2 Storage

AWS:
• Infrastructure
• Replication for data for EBS volumes & EFS drives
• Replacing faulty hardware
• Ensuring their employees cannot access your data

User:
• Setting up backup / snapshot procedures
• Setting up data encryption
• Responsibility of any data on the drives
• Understanding the risk of using EC2 Instance Store


EC2 Instance Storage - Summary

• EBS volumes:
  • network drives attached to one EC2 instance at a time
  • Mapped to an Availability Zones
  • Can use EBS Snapshots for backups / transferring EBS volumes across AZ
• AMI: create ready-to-use EC2 instances with our customizations
• EC2 Image Builder: automatically build, test and distribute AMIs
• EC2 Instance Store:
  • High performance hardware disk attached to our EC2 instance
  • Lost if our instance is stopped / terminated
• EFS: network file system, can be attached to 100s of instances in a region
• EFS-IA: cost-optimized storage class for infrequent accessed files
• FSx for Windows: Network File System for Windows servers
• FSx for Lustre: High Performance Computing Linux file system