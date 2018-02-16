/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 22:31:12 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/02/16 02:58:54 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OTOOL_H
# define NM_OTOOL_H

# include <sys/mman.h>
# include <stdbool.h>

# include <mach-o/loader.h>
# include <mach-o/fat.h>

# include <libft.h>
# include <public.h>

typedef struct mach_header					t_mach_header;
typedef struct mach_header_64				t_mach_header_64;
typedef struct load_command					t_load_command;
typedef struct segment_command				t_segment_command_32;
typedef struct segment_command_64			t_segment_command_64;
typedef struct section						t_section_32;
typedef struct section_64					t_section_64;
typedef struct fvmlib						t_fvmlib;
typedef struct fvmlib_command				t_fvmlib_command;
typedef struct dylib						t_dylib;
typedef struct dylib_command				t_dylib_command;
typedef struct sub_framework_command		t_sub_framework_command;
typedef struct sub_client_command			t_sub_client_command;
typedef struct sub_umbrella_command			t_sub_umbrella_command;
typedef struct sub_library_command			t_sub_library_command;
typedef struct prebound_dylib_command		t_prebound_dylib_command;
typedef struct dylinker_command				t_dylinker_command;
typedef struct thread_command				t_thread_command;
typedef struct routines_command				t_routines_command_32;
typedef struct routines_command_64			t_routines_command_64;
typedef struct symtab_command				t_symtab_command;
typedef struct dysymtab_command				t_dysymtab_command;
typedef struct dylib_table_of_contents		t_dylib_table_of_contents;
typedef struct dylib_module					t_dylib_module_32;
typedef struct dylib_module_64				t_dylib_module_64;
typedef struct dylib_reference				t_dylib_reference;
typedef struct twolevel_hints_command		t_twolevel_hints_command;
typedef struct twolevel_hint				t_twolevel_hint;
typedef struct prebind_cksum_command		t_prebind_cksum_command;
typedef struct uuid_command					t_uuid_command;
typedef struct rpath_command				t_rpath_command;
typedef struct linkedit_data_command		t_linkedit_data_command;
typedef struct encryption_info_command		t_encryption_info_command_32;
typedef struct encryption_info_command_64	t_encryption_info_command_64;
typedef struct version_min_command			t_version_min_command;
typedef struct dyld_info_command			t_dyld_info_command;
typedef struct linker_option_command		t_linker_option_command;
typedef struct symseg_command				t_symseg_command;
typedef struct ident_command				t_ident_command;
typedef struct fvmfile_command				t_fvmfile_command;
typedef struct entry_point_command			t_entry_point_command;
typedef struct source_version_command		t_source_version_command;
typedef struct data_in_code_entry			t_data_in_code_entry;
typedef struct tlv_descript					t_tlv_descript;

typedef struct fat_header					t_fat_header;
typedef struct fat_arch						t_fat_arch;
typedef struct fat_arch_64					t_fat_arch_64;

typedef union				u_cmd {
	t_load_command			load;
	t_segment_command_32	name;
	t_segment_command_32	seg32;
	t_segment_command_64	seg64;
	t_fvmlib_command		fvmlib;
	t_dylib_command			dylib;
}							t_cmd;

typedef struct				s_mem {
	u8						*data;
	u64						addr;
	u64						size;
}							t_mem;

typedef struct				s_vm {
	t_mem					mem;
	u32						ncmds;
	const char				*cpu;
	bool					is_swap;
	bool					is_64;
	bool					is_fat;
}							t_vm;

t_mem						map(char *filename);
int							get_vm(t_vm *f, t_mem mem);
const char					*get_cpu(cpu_type_t cpu, bool is_swap);

void						putdata(t_vm vm, u8 *data, size_t size, size_t addr);

u32							s(u32 x, bool is_swap);
u64							sl(u64 x, bool is_swap);
u32							swap(u32 i);
u64							swap_64(u64 i);
void						swap_header(t_mach_header *header, bool is_swap);
void						swap_load(t_load_command *cmd, bool is_swap);
void						swap_segment_64(t_segment_command_64 *seg, bool is_swap);
void						swap_segment_32(t_segment_command_32 *seg, bool is_swap);
void						swap_section_64(t_section_64 *sect, bool is_swap);
void						swap_section_32(t_section_32 *sect, bool is_swap);

# define BREAK(A) do { return(1000000 + 1000 * __LINE__ + A); } while (0)

# define CHECK_LEN(l) do { if (l > vm.mem.size) {\
	printf("failed check len %llu against size %llu\nfile: %s line: %i\n", l, vm.mem.size, __FILE__, __LINE__);\
	BREAK(__COUNTER__);\
 }} while (0)

#endif
