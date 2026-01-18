### Phase 1: TCP Foundations (Baseline)
**Goal:** Accept TCP connections and forward data to a single backend.

- Create listening socket
- Accept client connections
- Connect to one backend server
- Forward data (blocking I/O is OK here)
- Handle clean shutdowns

---

### Phase 2: Non-Blocking I/O + epoll
**Goal:** Scale beyond one connection.

- Set sockets to non-blocking mode
- Introduce `epoll`
- Handle read/write readiness
- Support multiple simultaneous connections

---

### Phase 3: Connection Abstraction
**Goal:** Make the system manageable and extensible.

- Introduce a `connection` struct
- Track:
  - client fd
  - backend fd
  - timestamps
  - byte counters
- Implement proper teardown logic

---

### Phase 4: Hash-Based Load Balancer
**Goal:** Distribute connections across multiple backends.

- Parse backend list from config
- Implement hash function
- Select backend per connection
- Track active connections per backend

---

### Phase 5: Backend Health Checks
**Goal:** Make the system resilient.

- Periodic TCP health probes
- Mark backends healthy/unhealthy
- Skip unhealthy backends in hash selection
- Auto-recover backends

---

### Phase 6: Observability & Logging
**Goal:** Make the system observable.

- Structured logs:
  - connection accepted
  - backend chosen
  - bytes transferred
  - errors
- Per-backend metrics
- Drop/error counters

---

### Phase 7: Performance Optimizations
**Goal:** Improve throughput and latency.

- Use edge-triggered `epoll`
- Reduce syscalls
- Tune socket options
- Optional zero-copy (`splice`)

---

### Phase 8: Hardening & Cleanup
**Goal:** Make it production-quality.

- Graceful shutdown
- Resource leak checks
- Stress testing (`wrk`, `iperf`)
- Error-path validation
