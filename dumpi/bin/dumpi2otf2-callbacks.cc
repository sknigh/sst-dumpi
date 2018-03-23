#include <dumpi/bin/dumpi2otf2-defs.h>
#include <dumpi/libotf2dump/otf2writer.h>
#include <assert.h>

// Some leftovers from the previous implementation

//int report_MPI_Group_size(const dumpi_group_size *prm, uint16_t thread, const dumpi_time *cpu, const dumpi_time *wall, const dumpi_perfinfo *perf, void *uarg) {
//  DUMPI_ENTERING();
//  auto dumpi_size = prm->size;
//  auto otf2_size = args->mpi_group[prm->group].size();
//  if (dumpi_size != otf2_size) printf("Error: MPI_Group_rank() for ID %i was %i, but expected %i.\n", prm->group, dumpi_size, otf2_size);
//  DUMPI_RETURNING();
//}

//int report_MPI_Comm_group(const dumpi_comm_group *prm, uint16_t thread, const dumpi_time *cpu, const dumpi_time *wall, const dumpi_perfinfo *perf, void *uarg) {
//  DUMPI_ENTERING();
//  // NULL indicates invalid parameters
//  if (prm->group != DUMPI_COMM_NULL) {
//    // Useful for settings MPI_COMM_WORLD's group ID to the implementation's default, otherwise it overwrites known parameters.
//    args->mpi_comm[prm->comm].group = prm->group;
//  }
//  DUMPI_RETURNING();
//}

//// C++17/20 have nifty STL set operations that operate on arbitrary iterators (std::set_union, std::set_intersection, etc...)
//// Unfortunately, this code targets C++11

//int report_MPI_Group_union(const dumpi_group_union *prm, uint16_t thread, const dumpi_time *cpu, const dumpi_time *wall, const dumpi_perfinfo *perf, void *uarg) {
//  DUMPI_ENTERING();
//  auto g1_it = args->mpi_group[prm->group1].begin();
//  auto g2_it = args->mpi_group[prm->group2].begin();
//  auto g1_end = args->mpi_group[prm->group1].end();
//  auto g2_end = args->mpi_group[prm->group2].end();
//  auto dest = std::back_inserter(args->mpi_group[prm->newgroup]);

//  // Set Union
//  while (true)
//  {
//      if (g1_it==g1_end) { std::copy(g2_it,g2_end,dest); break; }
//      if (g2_it==g2_end) { std::copy(g1_it,g1_end,dest); break; }

//      if (*g1_it<*g2_it) { *dest = *g1_it; ++g1_it; }
//      else if (*g2_it<*g1_it) { *dest = *g2_it; ++g2_it; }
//      else { *dest = *g1_it; ++g1_it; ++g2_it; }
//      ++dest;
//  }

//  DUMPI_RETURNING();
//}

//int report_MPI_Group_intersection(const dumpi_group_intersection *prm, uint16_t thread, const dumpi_time *cpu, const dumpi_time *wall, const dumpi_perfinfo *perf, void *uarg) {
//  DUMPI_ENTERING();
//  auto g1_it = args->mpi_group[prm->group1].begin();
//  auto g2_it = args->mpi_group[prm->group2].begin();
//  auto g1_end = args->mpi_group[prm->group1].end();
//  auto g2_end = args->mpi_group[prm->group2].end();
//  auto dest = std::back_inserter(args->mpi_group[prm->newgroup]);

//  // Set Intersection
//  while (g1_it!=g1_end && g2_it!=g2_end)
//  {
//    if (*g1_it<*g2_it) ++g1_it;
//    else if (*g2_it<*g1_it) ++g2_it;
//    else {
//      *dest = *g1_it;
//      ++dest; ++g1_it; ++g2_it;
//    }
//  }

//  DUMPI_RETURNING();
//}

//int report_MPI_Group_difference(const dumpi_group_difference *prm, uint16_t thread, const dumpi_time *cpu, const dumpi_time *wall, const dumpi_perfinfo *perf, void *uarg) {
//  DUMPI_ENTERING();

//  auto g1_it = args->mpi_group[prm->group1].begin();
//  auto g2_it = args->mpi_group[prm->group2].begin();
//  auto g1_end = args->mpi_group[prm->group1].end();
//  auto g2_end = args->mpi_group[prm->group2].end();
//  auto dest = std::back_inserter(args->mpi_group[prm->newgroup]);

//  // Set Difference
//  while (g1_it != g1_end) {
//    if (g2_it == g2_end) { std::copy(g1_it, g1_end, dest); break; }

//    if (*g1_it < *g2_it) {
//      *dest++ = *g1_it++;
//    } else {
//      if (! (*g2_it < *g1_it)) {
//        ++g1_it;
//      }
//      ++g2_it;
//    }
//  }

//  DUMPI_RETURNING();
//}

//int report_MPI_Group_incl(const dumpi_group_incl *prm, uint16_t thread, const dumpi_time *cpu, const dumpi_time *wall, const dumpi_perfinfo *perf, void *uarg) {
//  DUMPI_ENTERING();

//  // Creates a new group that includes the listed ranks
//  auto new_group = args->mpi_group[prm->newgroup];

//  for (int i = 0; i < prm->count; i++)
//    new_group.push_back(prm->ranks[i]);

//  DUMPI_RETURNING();
//}

//int report_MPI_Group_excl(const dumpi_group_excl *prm, uint16_t thread, const dumpi_time *cpu, const dumpi_time *wall, const dumpi_perfinfo *perf, void *uarg) {
//  DUMPI_ENTERING();

//  // Creates a new group that excludes the listed ranks
//  auto new_group = args->mpi_group[prm->newgroup];
//  auto old_group = args->mpi_group[prm->group];

//  for (int i = 0; i < old_group.size(); i++) {
//    bool exclude = false;
//    for (int j = 0; j < prm->count; j++) {
//      if (prm->ranks[j] == i) {
//        exclude = true;
//        break;
//      }
//    }
//    if (!exclude) new_group.push_back(old_group[i]);
//  }

//  DUMPI_RETURNING();
//}

//int report_MPI_Group_range_incl(const dumpi_group_range_incl *prm, uint16_t thread, const dumpi_time *cpu, const dumpi_time *wall, const dumpi_perfinfo *perf, void *uarg) {
//  DUMPI_ENTERING();
//  args->mpi_group[prm->newgroup] = args->mpi_group[prm->group];
//  for (int i = 0; i < prm->count; i++)
//    for(int j = prm->ranges[i][0]; j < prm->ranges[i][1]; j+=prm->ranges[i][2])
//      args->mpi_group[prm->newgroup].push_back(j);
//  DUMPI_RETURNING();
//}

//int report_MPI_Comm_dup(const dumpi_comm_dup *prm, uint16_t thread, const dumpi_time *cpu, const dumpi_time *wall, const dumpi_perfinfo *perf, void *uarg) {
//  DUMPI_ENTERING();
//  args->mpi_comm[prm->newcomm] = args->mpi_comm[prm->oldcomm];
//  DUMPI_RETURNING();
//}

//int report_MPI_Comm_create(const dumpi_comm_create *prm, uint16_t thread, const dumpi_time *cpu, const dumpi_time *wall, const dumpi_perfinfo *perf, void *uarg) {
//  DUMPI_ENTERING();
//  MPI_comm new_comm = MPI_comm("", prm->oldcomm, prm->newcomm, prm->group);
//  args->mpi_comm[prm->newcomm] = new_comm;
//  DUMPI_RETURNING();
//}

//int report_MPI_Comm_split(const dumpi_comm_split *prm, uint16_t thread, const dumpi_time *cpu, const dumpi_time *wall, const dumpi_perfinfo *perf, void *uarg) {
//  DUMPI_ENTERING();
//  // TODO This is an architectural issue. We can't know the result of a comm split until
//  // after the def file would have been written. We should not use global def files because of this
//  // One fix would be to write each def file individually
//  WARN_UNUSED(true);
//  DUMPI_RETURNING();
//}

//int report_MPI_Comm_free(const dumpi_comm_free *prm, uint16_t thread, const dumpi_time *cpu, const dumpi_time *wall, const dumpi_perfinfo *perf, void *uarg) {
//  DUMPI_ENTERING();
//  // TODO: What happens after a comm is freed? The implementation could reuse the id and overwrite its value in the final Def file.
//  WARN_UNUSED(true);
//  DUMPI_RETURNING();
//}

// Generates a captureless lambda function signature for an undumpi callback
#define CBACK_INIT(struct_name) \
  cbacks->on_ ## struct_name = [](const dumpi_ ## struct_name *prm, uint16_t thread, const dumpi_time *cpu, const dumpi_time *wall, const dumpi_perfinfo *perf, void *userarg)

// Boilerplate initialization
#define MACRO_INIT() \
  auto args = (DumpiArgs*)userarg; \
  auto& otf2_writer = args->otf2_writer; \

// Boilerplate return
#define MACRO_RET() return 1;

// Macros for time manipulation
#define START convert_time(wall->start)
#define STOP convert_time(wall->stop)
#define TIME START, STOP

// A wrapper for calls that do not record parameters in OTF2
#define GENERIC_CALL(name) \
  MACRO_INIT(); \
  otf2_writer.generic_call(TIME, name); \
  return 1;

// Turns a dumpi_clock struct into an integer of total nanoseconds
static inline uint32_t convert_time(dumpi_clock c) {
  return (((uint64_t)c.sec) * 1E9) + (uint64_t)c.nsec;
}

// Partially generated using set_callbacks() in dumpi2ascii-callbacks.cc and this vim substitution:
// :%s/^.*->on_\(.\{-}\)\(\s*\)= report_\(.\{-}\)\s*;$/  CBACK_INIT(\1)\2{ GENERIC_CALL("\3"); };/g
void set_callbacks(libundumpi_callbacks *cbacks) {
  assert(cbacks != NULL);
  CBACK_INIT(send)                      { MACRO_INIT(); otf2_writer.mpi_send(TIME, prm->datatype, prm->count, prm->dest, prm->comm, prm->tag); MACRO_RET(); };
  CBACK_INIT(recv)                      { MACRO_INIT(); otf2_writer.mpi_recv(TIME, prm->datatype, prm->count, prm->source, prm->comm, prm->tag); MACRO_RET(); };
  CBACK_INIT(get_count)                 { GENERIC_CALL("MPI_Get_count"); };
  CBACK_INIT(bsend)                     { GENERIC_CALL("MPI_Bsend"); };
  CBACK_INIT(ssend)                     { GENERIC_CALL("MPI_Ssend"); };
  CBACK_INIT(rsend)                     { GENERIC_CALL("MPI_Rsend"); };
  CBACK_INIT(buffer_attach)             { GENERIC_CALL("MPI_Buffer_attach"); };
  CBACK_INIT(buffer_detach)             { GENERIC_CALL("MPI_Buffer_detach"); };
  CBACK_INIT(isend)                     { MACRO_INIT(); otf2_writer.mpi_isend(TIME, prm->datatype, prm->count, prm->dest, prm->comm, prm->tag, prm->request); MACRO_RET(); };
  CBACK_INIT(ibsend)                    { GENERIC_CALL("MPI_Ibsend"); };
  CBACK_INIT(issend)                    { GENERIC_CALL("MPI_Issend"); };
  CBACK_INIT(irsend)                    { GENERIC_CALL("MPI_Irsend"); };
  CBACK_INIT(irecv)                     { MACRO_INIT(); otf2_writer.mpi_irecv(TIME, prm->datatype, prm->count, prm->source, prm->comm, prm->tag, prm->request); MACRO_RET(); };
  CBACK_INIT(wait)                      { MACRO_INIT(); otf2_writer.mpi_wait(TIME, prm->request); MACRO_RET(); };
  CBACK_INIT(test)                      { MACRO_INIT(); otf2_writer.mpi_test(TIME, prm->request, prm->flag); MACRO_RET(); };
  CBACK_INIT(request_free)              { GENERIC_CALL("MPI_Request_free"); };
  CBACK_INIT(waitany)                   { MACRO_INIT(); otf2_writer.mpi_waitany(TIME, prm->requests[prm->index]); MACRO_RET(); };
  CBACK_INIT(testany)                   { MACRO_INIT(); otf2_writer.mpi_testany(TIME, prm->requests, prm->index, prm->flag); MACRO_RET(); };
  CBACK_INIT(waitall)                   { MACRO_INIT(); otf2_writer.mpi_waitall(TIME, prm->count, prm->requests); MACRO_RET(); };
  CBACK_INIT(testall)                   { MACRO_INIT(); otf2_writer.mpi_testall(TIME, prm->count, prm->requests, prm->flag); MACRO_RET(); };
  CBACK_INIT(waitsome)                  { MACRO_INIT(); otf2_writer.mpi_waitsome(TIME, prm->requests, prm->outcount, prm->indices); MACRO_RET(); };
  CBACK_INIT(testsome)                  { MACRO_INIT(); otf2_writer.mpi_testsome(TIME, prm->requests, prm->outcount, prm->indices); MACRO_RET(); };
  CBACK_INIT(iprobe)                    { GENERIC_CALL("MPI_Iprobe"); };
  CBACK_INIT(probe)                     { GENERIC_CALL("MPI_Probe"); };
  CBACK_INIT(cancel)                    { GENERIC_CALL("MPI_Cancel"); };
  CBACK_INIT(test_cancelled)            { GENERIC_CALL("MPI_Test_cancelled"); };
  CBACK_INIT(send_init)                 { GENERIC_CALL("MPI_Send_init"); };
  CBACK_INIT(bsend_init)                { GENERIC_CALL("MPI_Bsend_init"); };
  CBACK_INIT(ssend_init)                { GENERIC_CALL("MPI_Ssend_init"); };
  CBACK_INIT(rsend_init)                { GENERIC_CALL("MPI_Rsend_init"); };
  CBACK_INIT(recv_init)                 { GENERIC_CALL("MPI_Recv_init"); };
  CBACK_INIT(start)                     { GENERIC_CALL("MPI_Start"); };
  CBACK_INIT(startall)                  { GENERIC_CALL("MPI_Startall"); };
  CBACK_INIT(sendrecv)                  { GENERIC_CALL("MPI_Sendrecv"); };
  CBACK_INIT(sendrecv_replace)          { GENERIC_CALL("MPI_Sendrecv_replace"); };
  CBACK_INIT(type_contiguous)           { GENERIC_CALL("MPI_Type_contiguous"); };
  CBACK_INIT(type_vector)               { GENERIC_CALL("MPI_Type_vector"); };
  CBACK_INIT(type_hvector)              { GENERIC_CALL("MPI_Type_hvector"); };
  CBACK_INIT(type_indexed)              { GENERIC_CALL("MPI_Type_indexed"); };
  CBACK_INIT(type_hindexed)             { GENERIC_CALL("MPI_Type_hindexed"); };
  CBACK_INIT(type_struct)               { GENERIC_CALL("MPI_Type_struct"); };
  CBACK_INIT(address)                   { GENERIC_CALL("MPI_Address"); };
  CBACK_INIT(type_extent)               { GENERIC_CALL("MPI_Type_extent"); };
  CBACK_INIT(type_size)                 { GENERIC_CALL("MPI_Type_size"); };
  CBACK_INIT(type_lb)                   { GENERIC_CALL("MPI_Type_lb"); };
  CBACK_INIT(type_ub)                   { GENERIC_CALL("MPI_Type_ub"); };
  CBACK_INIT(type_commit)               { GENERIC_CALL("MPI_Type_commit"); };
  CBACK_INIT(type_free)                 { GENERIC_CALL("MPI_Type_free"); };
  CBACK_INIT(get_elements)              { GENERIC_CALL("MPI_Get_elements"); };
  CBACK_INIT(pack)                      { GENERIC_CALL("MPI_Pack"); };
  CBACK_INIT(unpack)                    { GENERIC_CALL("MPI_Unpack"); };
  CBACK_INIT(pack_size)                 { GENERIC_CALL("MPI_Pack_size"); };
  CBACK_INIT(barrier)                   { MACRO_INIT(); otf2_writer.mpi_barrier(TIME, prm->comm); MACRO_RET(); };
  CBACK_INIT(bcast)                     { MACRO_INIT(); otf2_writer.mpi_bcast(TIME, prm->count, prm->datatype, prm->root, prm->comm); MACRO_RET(); };
  CBACK_INIT(gather)                    { MACRO_INIT(); otf2_writer.mpi_gather(TIME, prm->sendcount, prm->sendtype, prm->recvcount, prm->recvtype, prm->root, prm->comm); MACRO_RET(); };
  CBACK_INIT(gatherv)                   { GENERIC_CALL("MPI_Gatherv"); };
  CBACK_INIT(scatter)                   { MACRO_INIT(); otf2_writer.mpi_scatter(TIME, prm->sendcount, prm->sendtype, prm->recvcount, prm->recvtype, prm->root, prm->comm); MACRO_RET(); };
  CBACK_INIT(scatterv)                  { GENERIC_CALL("MPI_Scatterv"); };
  CBACK_INIT(allgather)                 { MACRO_INIT(); otf2_writer.mpi_allgather(TIME, prm->sendcount, prm->sendtype, prm->recvcount, prm->recvtype, prm->comm); MACRO_RET(); };
  CBACK_INIT(allgatherv)                { GENERIC_CALL("MPI_Allgatherv"); };
  CBACK_INIT(alltoall)                  { MACRO_INIT(); otf2_writer.mpi_alltoall(TIME, prm->sendcount, prm->sendtype, prm->recvcount, prm->recvtype, prm->comm); MACRO_RET(); };
  CBACK_INIT(alltoallv)                 { GENERIC_CALL("MPI_Alltoallv"); };
  CBACK_INIT(reduce)                    { MACRO_INIT(); otf2_writer.mpi_reduce(TIME, prm->count, prm->datatype, prm->root, prm->comm); MACRO_RET(); };
  CBACK_INIT(op_create)                 { GENERIC_CALL("MPI_Op_create"); };
  CBACK_INIT(op_free)                   { GENERIC_CALL("MPI_Op_free"); };
  CBACK_INIT(allreduce)                 { MACRO_INIT(); otf2_writer.mpi_allreduce(TIME, prm->count, prm->datatype, prm->comm); MACRO_RET(); };
  CBACK_INIT(reduce_scatter)            { MACRO_INIT(); otf2_writer.mpi_reduce_scatter(TIME, prm->recvcounts, prm->datatype, prm->comm); MACRO_RET(); };
  CBACK_INIT(scan)                      { GENERIC_CALL("MPI_Scan"); };
  CBACK_INIT(group_size)                { GENERIC_CALL("MPI_Group_size"); };
  CBACK_INIT(group_rank)                { GENERIC_CALL("MPI_Group_rank"); };
  CBACK_INIT(group_translate_ranks)     { GENERIC_CALL("MPI_Group_translate_ranks"); };
  CBACK_INIT(group_compare)             { GENERIC_CALL("MPI_Group_compare"); };
  CBACK_INIT(comm_group)                { GENERIC_CALL("MPI_Comm_group"); };
  CBACK_INIT(group_union)               { GENERIC_CALL("MPI_Group_union"); };
  CBACK_INIT(group_intersection)        { GENERIC_CALL("MPI_Group_intersection"); };
  CBACK_INIT(group_difference)          { GENERIC_CALL("MPI_Group_difference"); };
  CBACK_INIT(group_incl)                { GENERIC_CALL("MPI_Group_incl"); };
  CBACK_INIT(group_excl)                { GENERIC_CALL("MPI_Group_excl"); };
  CBACK_INIT(group_range_incl)          { GENERIC_CALL("MPI_Group_range_incl"); };
  CBACK_INIT(group_range_excl)          { GENERIC_CALL("MPI_Group_range_excl"); };
  CBACK_INIT(group_free)                { GENERIC_CALL("MPI_Group_free"); };
  CBACK_INIT(comm_size)                 { GENERIC_CALL("MPI_Comm_size"); };
  CBACK_INIT(comm_rank)                 { GENERIC_CALL("MPI_Comm_rank"); };
  CBACK_INIT(comm_compare)              { GENERIC_CALL("MPI_Comm_compare"); };
  CBACK_INIT(comm_dup)                  { GENERIC_CALL("MPI_Comm_dup"); };
  CBACK_INIT(comm_create)               { GENERIC_CALL("MPI_Comm_create"); };
  CBACK_INIT(comm_split)                { GENERIC_CALL("MPI_Comm_split"); };
  CBACK_INIT(comm_free)                 { GENERIC_CALL("MPI_Comm_free"); };
  CBACK_INIT(comm_test_inter)           { GENERIC_CALL("MPI_Comm_test_inter"); };
  CBACK_INIT(comm_remote_size)          { GENERIC_CALL("MPI_Comm_remote_size"); };
  CBACK_INIT(comm_remote_group)         { GENERIC_CALL("MPI_Comm_remote_group"); };
  CBACK_INIT(intercomm_create)          { GENERIC_CALL("MPI_Intercomm_create"); };
  CBACK_INIT(intercomm_merge)           { GENERIC_CALL("MPI_Intercomm_merge"); };
  CBACK_INIT(keyval_create)             { GENERIC_CALL("MPI_Keyval_create"); };
  CBACK_INIT(keyval_free)               { GENERIC_CALL("MPI_Keyval_free"); };
  CBACK_INIT(attr_put)                  { GENERIC_CALL("MPI_Attr_put"); };
  CBACK_INIT(attr_get)                  { GENERIC_CALL("MPI_Attr_get"); };
  CBACK_INIT(attr_delete)               { GENERIC_CALL("MPI_Attr_delete"); };
  CBACK_INIT(topo_test)                 { GENERIC_CALL("MPI_Topo_test"); };
  CBACK_INIT(cart_create)               { GENERIC_CALL("MPI_Cart_create"); };
  CBACK_INIT(dims_create)               { GENERIC_CALL("MPI_Dims_create"); };
  CBACK_INIT(graph_create)              { GENERIC_CALL("MPI_Graph_create"); };
  CBACK_INIT(graphdims_get)             { GENERIC_CALL("MPI_Graphdims_get"); };
  CBACK_INIT(graph_get)                 { GENERIC_CALL("MPI_Graph_get"); };
  CBACK_INIT(cartdim_get)               { GENERIC_CALL("MPI_Cartdim_get"); };
  CBACK_INIT(cart_get)                  { GENERIC_CALL("MPI_Cart_get"); };
  CBACK_INIT(cart_rank)                 { GENERIC_CALL("MPI_Cart_rank"); };
  CBACK_INIT(cart_coords)               { GENERIC_CALL("MPI_Cart_coords"); };
  CBACK_INIT(graph_neighbors_count)     { GENERIC_CALL("MPI_Graph_neighbors_count"); };
  CBACK_INIT(graph_neighbors)           { GENERIC_CALL("MPI_Graph_neighbors"); };
  CBACK_INIT(cart_shift)                { GENERIC_CALL("MPI_Cart_shift"); };
  CBACK_INIT(cart_sub)                  { GENERIC_CALL("MPI_Cart_sub"); };
  CBACK_INIT(cart_map)                  { GENERIC_CALL("MPI_Cart_map"); };
  CBACK_INIT(graph_map)                 { GENERIC_CALL("MPI_Graph_map"); };
  CBACK_INIT(get_processor_name)        { GENERIC_CALL("MPI_Get_processor_name"); };
  CBACK_INIT(get_version)               { GENERIC_CALL("MPI_Get_version"); };
  CBACK_INIT(errhandler_create)         { GENERIC_CALL("MPI_Errhandler_create"); };
  CBACK_INIT(errhandler_set)            { GENERIC_CALL("MPI_Errhandler_set"); };
  CBACK_INIT(errhandler_get)            { GENERIC_CALL("MPI_Errhandler_get"); };
  CBACK_INIT(errhandler_free)           { GENERIC_CALL("MPI_Errhandler_free"); };
  CBACK_INIT(error_string)              { GENERIC_CALL("MPI_Error_string"); };
  CBACK_INIT(error_class)               { GENERIC_CALL("MPI_Error_class"); };
  CBACK_INIT(wtime)                     { GENERIC_CALL("MPI_Wtime"); };
  CBACK_INIT(wtick)                     { GENERIC_CALL("MPI_Wtick"); };
  CBACK_INIT(init)                      { GENERIC_CALL("MPI_Init"); };
  CBACK_INIT(finalize)                  { GENERIC_CALL("MPI_Finalize"); };
  CBACK_INIT(initialized)               { GENERIC_CALL("MPI_Initialized"); };
  CBACK_INIT(abort)                     { GENERIC_CALL("MPI_Abort"); };
  CBACK_INIT(close_port)                { GENERIC_CALL("MPI_Close_port"); };
  CBACK_INIT(comm_accept)               { GENERIC_CALL("MPI_Comm_accept"); };
  CBACK_INIT(comm_connect)              { GENERIC_CALL("MPI_Comm_connect"); };
  CBACK_INIT(comm_disconnect)           { GENERIC_CALL("MPI_Comm_disconnect"); };
  CBACK_INIT(comm_get_parent)           { GENERIC_CALL("MPI_Comm_get_parent"); };
  CBACK_INIT(comm_join)                 { GENERIC_CALL("MPI_Comm_join"); };
  CBACK_INIT(comm_spawn)                { GENERIC_CALL("MPI_Comm_spawn"); };
  CBACK_INIT(comm_spawn_multiple)       { GENERIC_CALL("MPI_Comm_spawn_multiple"); };
  CBACK_INIT(lookup_name)               { GENERIC_CALL("MPI_Lookup_name"); };
  CBACK_INIT(open_port)                 { GENERIC_CALL("MPI_Open_port"); };
  CBACK_INIT(publish_name)              { GENERIC_CALL("MPI_Publish_name"); };
  CBACK_INIT(unpublish_name)            { GENERIC_CALL("MPI_Unpublish_name"); };
  CBACK_INIT(accumulate)                { GENERIC_CALL("MPI_Accumulate"); };
  CBACK_INIT(get)                       { GENERIC_CALL("MPI_Get"); };
  CBACK_INIT(put)                       { GENERIC_CALL("MPI_Put"); };
  CBACK_INIT(win_complete)              { GENERIC_CALL("MPI_Win_complete"); };
  CBACK_INIT(win_create)                { GENERIC_CALL("MPI_Win_create"); };
  CBACK_INIT(win_fence)                 { GENERIC_CALL("MPI_Win_fence"); };
  CBACK_INIT(win_free)                  { GENERIC_CALL("MPI_Win_free"); };
  CBACK_INIT(win_get_group)             { GENERIC_CALL("MPI_Win_get_group"); };
  CBACK_INIT(win_lock)                  { GENERIC_CALL("MPI_Win_lock"); };
  CBACK_INIT(win_post)                  { GENERIC_CALL("MPI_Win_post"); };
  CBACK_INIT(win_start)                 { GENERIC_CALL("MPI_Win_start"); };
  CBACK_INIT(win_test)                  { GENERIC_CALL("MPI_Win_test"); };
  CBACK_INIT(win_unlock)                { GENERIC_CALL("MPI_Win_unlock"); };
  CBACK_INIT(win_wait)                  { GENERIC_CALL("MPI_Win_wait"); };
  CBACK_INIT(alltoallw)                 { GENERIC_CALL("MPI_Alltoallw"); };
  CBACK_INIT(exscan)                    { GENERIC_CALL("MPI_Exscan"); };
  CBACK_INIT(add_error_class)           { GENERIC_CALL("MPI_Add_error_class"); };
  CBACK_INIT(add_error_code)            { GENERIC_CALL("MPI_Add_error_code"); };
  CBACK_INIT(add_error_string)          { GENERIC_CALL("MPI_Add_error_string"); };
  CBACK_INIT(comm_call_errhandler)      { GENERIC_CALL("MPI_Comm_call_errhandler"); };
  CBACK_INIT(comm_create_keyval)        { GENERIC_CALL("MPI_Comm_create_keyval"); };
  CBACK_INIT(comm_delete_attr)          { GENERIC_CALL("MPI_Comm_delete_attr"); };
  CBACK_INIT(comm_free_keyval)          { GENERIC_CALL("MPI_Comm_free_keyval"); };
  CBACK_INIT(comm_get_attr)             { GENERIC_CALL("MPI_Comm_get_attr"); };
  CBACK_INIT(comm_get_name)             { GENERIC_CALL("MPI_Comm_get_name"); };
  CBACK_INIT(comm_set_attr)             { GENERIC_CALL("MPI_Comm_set_attr"); };
  CBACK_INIT(comm_set_name)             { GENERIC_CALL("MPI_Comm_set_name"); };
  CBACK_INIT(file_call_errhandler)      { GENERIC_CALL("MPI_File_call_errhandler"); };
  CBACK_INIT(grequest_complete)         { GENERIC_CALL("MPI_Grequest_complete"); };
  CBACK_INIT(grequest_start)            { GENERIC_CALL("MPI_Grequest_start"); };
  CBACK_INIT(init_thread)               { GENERIC_CALL("MPI_Init_thread"); };
  CBACK_INIT(is_thread_main)            { GENERIC_CALL("MPI_Is_thread_main"); };
  CBACK_INIT(query_thread)              { GENERIC_CALL("MPI_Query_thread"); };
  CBACK_INIT(status_set_cancelled)      { GENERIC_CALL("MPI_Status_set_cancelled"); };
  CBACK_INIT(status_set_elements)       { GENERIC_CALL("MPI_Status_set_elements"); };
  CBACK_INIT(type_create_keyval)        { GENERIC_CALL("MPI_Type_create_keyval"); };
  CBACK_INIT(type_delete_attr)          { GENERIC_CALL("MPI_Type_delete_attr"); };
  CBACK_INIT(type_dup)                  { GENERIC_CALL("MPI_Type_dup"); };
  CBACK_INIT(type_free_keyval)          { GENERIC_CALL("MPI_Type_free_keyval"); };
  CBACK_INIT(type_get_attr)             { GENERIC_CALL("MPI_Type_get_attr"); };
  CBACK_INIT(type_get_contents)         { GENERIC_CALL("MPI_Type_get_contents"); };
  CBACK_INIT(type_get_envelope)         { GENERIC_CALL("MPI_Type_get_envelope"); };
  CBACK_INIT(type_get_name)             { GENERIC_CALL("MPI_Type_get_name"); };
  CBACK_INIT(type_set_attr)             { GENERIC_CALL("MPI_Type_set_attr"); };
  CBACK_INIT(type_set_name)             { GENERIC_CALL("MPI_Type_set_name"); };
  CBACK_INIT(type_match_size)           { GENERIC_CALL("MPI_Type_match_size"); };
  CBACK_INIT(win_call_errhandler)       { GENERIC_CALL("MPI_Win_call_errhandler"); };
  CBACK_INIT(win_create_keyval)         { GENERIC_CALL("MPI_Win_create_keyval"); };
  CBACK_INIT(win_delete_attr)           { GENERIC_CALL("MPI_Win_delete_attr"); };
  CBACK_INIT(win_free_keyval)           { GENERIC_CALL("MPI_Win_free_keyval"); };
  CBACK_INIT(win_get_attr)              { GENERIC_CALL("MPI_Win_get_attr"); };
  CBACK_INIT(win_get_name)              { GENERIC_CALL("MPI_Win_get_name"); };
  CBACK_INIT(win_set_attr)              { GENERIC_CALL("MPI_Win_set_attr"); };
  CBACK_INIT(win_set_name)              { GENERIC_CALL("MPI_Win_set_name"); };
  CBACK_INIT(alloc_mem)                 { GENERIC_CALL("MPI_Alloc_mem"); };
  CBACK_INIT(comm_create_errhandler)    { GENERIC_CALL("MPI_Comm_create_errhandler"); };
  CBACK_INIT(comm_get_errhandler)       { GENERIC_CALL("MPI_Comm_get_errhandler"); };
  CBACK_INIT(comm_set_errhandler)       { GENERIC_CALL("MPI_Comm_set_errhandler"); };
  CBACK_INIT(file_create_errhandler)    { GENERIC_CALL("MPI_File_create_errhandler"); };
  CBACK_INIT(file_get_errhandler)       { GENERIC_CALL("MPI_File_get_errhandler"); };
  CBACK_INIT(file_set_errhandler)       { GENERIC_CALL("MPI_File_set_errhandler"); };
  CBACK_INIT(finalized)                 { GENERIC_CALL("MPI_Finalized"); };
  CBACK_INIT(free_mem)                  { GENERIC_CALL("MPI_Free_mem"); };
  CBACK_INIT(get_address)               { GENERIC_CALL("MPI_Get_address"); };
  CBACK_INIT(info_create)               { GENERIC_CALL("MPI_Info_create"); };
  CBACK_INIT(info_delete)               { GENERIC_CALL("MPI_Info_delete"); };
  CBACK_INIT(info_dup)                  { GENERIC_CALL("MPI_Info_dup"); };
  CBACK_INIT(info_free)                 { GENERIC_CALL("MPI_Info_free"); };
  CBACK_INIT(info_get)                  { GENERIC_CALL("MPI_Info_get"); };
  CBACK_INIT(info_get_nkeys)            { GENERIC_CALL("MPI_Info_get_nkeys"); };
  CBACK_INIT(info_get_nthkey)           { GENERIC_CALL("MPI_Info_get_nthkey"); };
  CBACK_INIT(info_get_valuelen)         { GENERIC_CALL("MPI_Info_get_valuelen"); };
  CBACK_INIT(info_set)                  { GENERIC_CALL("MPI_Info_set"); };
  CBACK_INIT(pack_external)             { GENERIC_CALL("MPI_Pack_external"); };
  CBACK_INIT(pack_external_size)        { GENERIC_CALL("MPI_Pack_external_size"); };
  CBACK_INIT(request_get_status)        { GENERIC_CALL("MPI_Request_get_status"); };
  CBACK_INIT(type_create_darray)        { GENERIC_CALL("MPI_Type_create_darray"); };
  CBACK_INIT(type_create_hindexed)      { GENERIC_CALL("MPI_Type_create_hindexed"); };
  CBACK_INIT(type_create_hvector)       { GENERIC_CALL("MPI_Type_create_hvector"); };
  CBACK_INIT(type_create_indexed_block) { GENERIC_CALL("MPI_Type_create_indexed_block"); };
  CBACK_INIT(type_create_resized)       { GENERIC_CALL("MPI_Type_create_resized"); };
  CBACK_INIT(type_create_struct)        { GENERIC_CALL("MPI_Type_create_struct"); };
  CBACK_INIT(type_create_subarray)      { GENERIC_CALL("MPI_Type_create_subarray"); };
  CBACK_INIT(type_get_extent)           { GENERIC_CALL("MPI_Type_get_extent"); };
  CBACK_INIT(type_get_true_extent)      { GENERIC_CALL("MPI_Type_get_true_extent"); };
  CBACK_INIT(unpack_external)           { GENERIC_CALL("MPI_Unpack_external"); };
  CBACK_INIT(win_create_errhandler)     { GENERIC_CALL("MPI_Win_create_errhandler"); };
  CBACK_INIT(win_get_errhandler)        { GENERIC_CALL("MPI_Win_get_errhandler"); };
  CBACK_INIT(win_set_errhandler)        { GENERIC_CALL("MPI_Win_set_errhandler"); };
  CBACK_INIT(file_open)                 { GENERIC_CALL("MPI_File_open"); };
  CBACK_INIT(file_close)                { GENERIC_CALL("MPI_File_close"); };
  CBACK_INIT(file_delete)               { GENERIC_CALL("MPI_File_delete"); };
  CBACK_INIT(file_set_size)             { GENERIC_CALL("MPI_File_set_size"); };
  CBACK_INIT(file_preallocate)          { GENERIC_CALL("MPI_File_preallocate"); };
  CBACK_INIT(file_get_size)             { GENERIC_CALL("MPI_File_get_size"); };
  CBACK_INIT(file_get_group)            { GENERIC_CALL("MPI_File_get_group"); };
  CBACK_INIT(file_get_amode)            { GENERIC_CALL("MPI_File_get_amode"); };
  CBACK_INIT(file_set_info)             { GENERIC_CALL("MPI_File_set_info"); };
  CBACK_INIT(file_get_info)             { GENERIC_CALL("MPI_File_get_info"); };
  CBACK_INIT(file_set_view)             { GENERIC_CALL("MPI_File_set_view"); };
  CBACK_INIT(file_get_view)             { GENERIC_CALL("MPI_File_get_view"); };
  CBACK_INIT(file_read_at)              { GENERIC_CALL("MPI_File_read_at"); };
  CBACK_INIT(file_read_at_all)          { GENERIC_CALL("MPI_File_read_at_all"); };
  CBACK_INIT(file_write_at)             { GENERIC_CALL("MPI_File_write_at"); };
  CBACK_INIT(file_write_at_all)         { GENERIC_CALL("MPI_File_write_at_all"); };
  CBACK_INIT(file_iread_at)             { GENERIC_CALL("MPI_File_iread_at"); };
  CBACK_INIT(file_iwrite_at)            { GENERIC_CALL("MPI_File_iwrite_at"); };
  CBACK_INIT(file_read)                 { GENERIC_CALL("MPI_File_read"); };
  CBACK_INIT(file_read_all)             { GENERIC_CALL("MPI_File_read_all"); };
  CBACK_INIT(file_write)                { GENERIC_CALL("MPI_File_write"); };
  CBACK_INIT(file_write_all)            { GENERIC_CALL("MPI_File_write_all"); };
  CBACK_INIT(file_iread)                { GENERIC_CALL("MPI_File_iread"); };
  CBACK_INIT(file_iwrite)               { GENERIC_CALL("MPI_File_iwrite"); };
  CBACK_INIT(file_seek)                 { GENERIC_CALL("MPI_File_seek"); };
  CBACK_INIT(file_get_position)         { GENERIC_CALL("MPI_File_get_position"); };
  CBACK_INIT(file_get_byte_offset)      { GENERIC_CALL("MPI_File_get_byte_offset"); };
  CBACK_INIT(file_read_shared)          { GENERIC_CALL("MPI_File_read_shared"); };
  CBACK_INIT(file_write_shared)         { GENERIC_CALL("MPI_File_write_shared"); };
  CBACK_INIT(file_iread_shared)         { GENERIC_CALL("MPI_File_iread_shared"); };
  CBACK_INIT(file_iwrite_shared)        { GENERIC_CALL("MPI_File_iwrite_shared"); };
  CBACK_INIT(file_read_ordered)         { GENERIC_CALL("MPI_File_read_ordered"); };
  CBACK_INIT(file_write_ordered)        { GENERIC_CALL("MPI_File_write_ordered"); };
  CBACK_INIT(file_seek_shared)          { GENERIC_CALL("MPI_File_seek_shared"); };
  CBACK_INIT(file_get_position_shared)  { GENERIC_CALL("MPI_File_get_position_shared"); };
  CBACK_INIT(file_read_at_all_begin)    { GENERIC_CALL("MPI_File_read_at_all_begin"); };
  CBACK_INIT(file_read_at_all_end)      { GENERIC_CALL("MPI_File_read_at_all_end"); };
  CBACK_INIT(file_write_at_all_begin)   { GENERIC_CALL("MPI_File_write_at_all_begin"); };
  CBACK_INIT(file_write_at_all_end)     { GENERIC_CALL("MPI_File_write_at_all_end"); };
  CBACK_INIT(file_read_all_begin)       { GENERIC_CALL("MPI_File_read_all_begin"); };
  CBACK_INIT(file_read_all_end)         { GENERIC_CALL("MPI_File_read_all_end"); };
  CBACK_INIT(file_write_all_begin)      { GENERIC_CALL("MPI_File_write_all_begin"); };
  CBACK_INIT(file_write_all_end)        { GENERIC_CALL("MPI_File_write_all_end"); };
  CBACK_INIT(file_read_ordered_begin)   { GENERIC_CALL("MPI_File_read_ordered_begin"); };
  CBACK_INIT(file_read_ordered_end)     { GENERIC_CALL("MPI_File_read_ordered_end"); };
  CBACK_INIT(file_write_ordered_begin)  { GENERIC_CALL("MPI_File_write_ordered_begin"); };
  CBACK_INIT(file_write_ordered_end)    { GENERIC_CALL("MPI_File_write_ordered_end"); };
  CBACK_INIT(file_get_type_extent)      { GENERIC_CALL("MPI_File_get_type_extent"); };
  CBACK_INIT(register_datarep)          { GENERIC_CALL("MPI_Register_datarep"); };
  CBACK_INIT(file_set_atomicity)        { GENERIC_CALL("MPI_File_set_atomicity"); };
  CBACK_INIT(file_get_atomicity)        { GENERIC_CALL("MPI_File_get_atomicity"); };
  CBACK_INIT(file_sync)                 { GENERIC_CALL("MPI_File_sync"); };
}
