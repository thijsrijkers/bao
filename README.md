# Bao

A high-performance Layer 4 (TCP) load balancer written in C, inspired by AWS Network Load Balancer (NLB).  
This project implements **hash-based load balancing** to consistently route client connections to backend servers while maintaining low latency and high throughput.

---

## Overview

This load balancer operates as a **full TCP proxy**:

- Accepts incoming TCP connections from clients
- Selects a backend server using a **hash-based algorithm**
- Establishes a backend TCP connection
- Proxies data bidirectionally using non-blocking I/O

The design focuses on **performance, correctness, and observability**, similar to production-grade infrastructure.

---

## Architecture

```pgsql
Client
  |
  | TCP
  v
+----------------------+
|  TCP Load Balancer   |
|----------------------|
| - Accept connections |
| - Hash scheduler     |
| - epoll event loop   |
| - Health checks      |
+----------+-----------+
           |
           | TCP
           v
   Backend Servers
```

---

## Load Balancing Algorithm

### Hash-Based Scheduling

```pgsql
backend_index = hash(client_ip, client_port) % healthy_backend_count
```

**Why Hashing?**

- Predictable routing
- Backend cache locality
- Simple and fast
- Common in L4 load balancers

---
