/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 22:31:12 by lgarczyn          #+#    #+#             */
/*   Updated: 2018/09/16 19:03:53 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OTOOL_H
# define NM_OTOOL_H

# include <sys/mman.h>
# include <stdbool.h>

# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <mach-o/nlist.h>

# include "libft.h"
# include "printf.h"

typedef struct mach_header					t_mach_header;
typedef struct mach_header_64				t_mach_header_64;
typedef struct load_command					t_load_cmd;
typedef struct segment_command				t_seg_cmd_32;
typedef struct segment_command_64			t_seg_cmd_64;
typedef struct section						t_section_32;
typedef struct section_64					t_section_64;
typedef struct fvmlib						t_fvmlib;
typedef struct fvmlib_command				t_fvmlib_cmd;
typedef struct dylib						t_dylib;
typedef struct dylib_command				t_dylib_cmd;
typedef struct sub_framework_command		t_sub_framework_cmd;
typedef struct sub_client_command			t_sub_client_cmd;
typedef struct sub_umbrella_command			t_sub_umbrella_cmd;
typedef struct sub_library_command			t_sub_library_cmd;
typedef struct prebound_dylib_command		t_prebound_dylib_cmd;
typedef struct dylinker_command				t_dylinker_cmd;
typedef struct thread_command				t_thread_cmd;
typedef struct routines_command				t_routines_cmd_32;
typedef struct routines_command_64			t_routines_cmd_64;
typedef struct symtab_command				t_symtab_cmd;
typedef struct dysymtab_command				t_dysymtab_cmd;
typedef struct dylib_table_of_contents		t_dylib_table_of_contents;
typedef struct dylib_module					t_dylib_module_32;
typedef struct dylib_module_64				t_dylib_module_64;
typedef struct dylib_reference				t_dylib_reference;
typedef struct twolevel_hints_command		t_twolevel_hints_cmd;
typedef struct twolevel_hint				t_twolevel_hint;
typedef struct prebind_cksum_command		t_prebind_cksum_cmd;
typedef struct uuid_command					t_uuid_cmd;
typedef struct rpath_command				t_rpath_cmd;
typedef struct linkedit_data_cmd			t_linkedit_data_cmd;
typedef struct encryption_info_command		t_encryption_info_cmd_32;
typedef struct encryption_info_command_64	t_encryption_info_cmd_64;
typedef struct version_min_command			t_version_min_cmd;
typedef struct dyld_info_command			t_dyld_info_cmd;
typedef struct linker_option_command		t_linker_option_cmd;
typedef struct ident_command				t_ident_cmd;
typedef struct fvmfile_command				t_fvmfile_cmd;
typedef struct entry_point_command			t_entry_point_cmd;
typedef struct source_version_command		t_source_version_cmd;
typedef struct data_in_code_entry			t_data_in_code_entry;
typedef struct tlv_descript					t_tlv_descript;

typedef struct fat_header					t_fat_header;
typedef struct fat_arch						t_fat_arch;
typedef struct fat_arch_64					t_fat_arch_64;

typedef struct nlist						t_nlist;
typedef struct nlist_64						t_nlist_64;

typedef struct		s_symdef {
	u32				name;
	u32				object;
}					t_symdef;

typedef union		u_cmd {
	u32				cmd;
	t_load_cmd		load;
	t_seg_cmd_32	name;
	t_seg_cmd_32	seg32;
	t_seg_cmd_64	seg64;
	t_fvmlib_cmd	fvmlib;
	t_dylib_cmd		dylib;
}					t_cmd;

# define AR_START	"!<arch>\n"
# define AR_END		"  `\n"

typedef struct		s_ar_header {
	char			name[16];
	char			date[12];
	char			uid[6];
	char			gid[6];
	char			mode[8];
	char			size[8];
	char			end[4];
	char			long_name[0];
}					t_ar_header;

typedef struct		s_ar_info {
	u32				header_len;
	u32				full_len;
	char			*name;
}					t_ar_info;

typedef struct		s_mem {
	u8				*data;
	u64				size;
	u8				*file;
	u64				offset;
}					t_mem;

typedef struct		s_sym_token {
	t_nlist_64		sym;
	u8				*name;
}					t_sym_token;

struct s_vm;

typedef enum		e_sorting {
	sort_alphabetical = 0,
	sort_numerical,
	no_sorting,
}					t_sorting;

typedef struct		s_target {
	bool			is_otool;
	bool			show_names;
	bool			show_cpu;

	bool			only_name;
	t_sorting		sorting;
	bool			reversed;

	bool			show_text;
	bool			show_data;
	bool			show_header;
	char			*target_seg;
	char			*target_sect;
}					t_target;

typedef enum		e_ftype {
	f_err = 0,
	f_object = 1,
	f_fat = 2,
	f_ranlib = 3,
}					t_ftype;

typedef struct		s_vm {
	t_mem			mem;
	t_ftype			type;
	t_target		target;
	cpu_type_t		cpu;
	u32				ncmds;
	t_ar_info		ar_info;
	bool			is_swap;
	bool			is_64;

	t_array			*sect_types;
	t_array			*sym_tokens;
}					t_vm;

int					map(t_mem *out, char *filename);
int					get_vm(t_vm *f, t_mem mem, t_target target);
int					check_ranlib_header(t_vm vm, u64 pos, t_ar_info *out);
t_mem				get_arch_map(t_vm vm, void *ptr, cpu_type_t *cpu);

t_mem				get_sub_mem(t_mem mem, u64 offset, u64 size);
int					check_string(t_vm vm, u8 *str);
int					array_push(t_array *array, void *data, size_t size);
void				free_arrays(t_vm *vm);

char				get_sect_type(char *name);
char				get_sym_type(t_nlist_64 sym, t_array *stypes);
t_ftype				get_type(void *p, bool *is_swap, bool *is_64);
const char			*get_cpu(cpu_type_t cpu);

void				disp_filename(t_vm vm, char *file, char *ar);
void				disp_data(t_vm *vm, u8 *data, size_t size, size_t addr);
void				disp_header(t_mach_header *header, bool is_swap);

void				disp_symtab(t_vm vm, t_array *sym, t_array *types);
int					store_symtab(t_vm vm, t_symtab_cmd cmd, t_array *tokens);

int					disp_file(t_mem mem, t_target target, char *file, char *ar);
int					disp_ranlib(t_vm vm, char *file);

int					filter_disp(t_target target, t_section_64 sec);

u32					s(u32 x, bool is_swap);
u64					sl(u64 x, bool is_swap);

t_load_cmd			read_load(void *cmd, bool is_swap);
t_seg_cmd_64		read_segment(void *p, bool is_swap, bool is_64);
t_section_64		read_section(void *p, bool is_swap, bool is_64);
t_symtab_cmd		read_symtab_cmd(void *p, bool is_swap);
t_nlist_64			read_sym_token(t_vm vm, void *p);

int					gen_filter(int r, char *p, char *f);

# define OK 0
# define ERR_MAGIC 132
# define ERR_MEM 133

# define WRAP(T) do { T } while (0)
# define WRAP_C(T) if (1) { T } else { }
# define BREAK WRAP( return(ERR_MEM); )

# define DEBUG false

# if (DEBUG)
#  define L() WRAP(printerr(" %s:%i\n", __FILE__, __LINE__);)
#  define PRINT_L(l) WRAP(printerr("%llu > %llu", (u64)l, vm.mem.size); L();)
#  define PRINT_R(r) WRAP(printerr("ERR = %llu", (u64)r); L();)
#  define PRINT_F(p, f, r) WRAP(printerr("%s: %s: %s\n", p, f, ft_strerror(r));)
#  define CHECK_LEN(l) WRAP(if (l > vm.mem.size) { PRINT_L(l); BREAK; })
#  define CHECK(t) WRAP(int r = t; if (r) {PRINT_R(r); return(r);})
# else
#  define PRINT_F(p, f, r) WRAP(printerr("%s: %s: %s\n", p, f, ft_strerror(r));)
#  define CHECK_LEN(l) WRAP(if (l > vm.mem.size) { BREAK; })
#  define CHECK(t) WRAP(int r = t; if (r) {return(r);})
# endif

# define CHECK_CLEAN(t, c) WRAP(int r = t; if (r) {c; return(r);})

# define GET_CHECKED_PTR(o, l) ({CHECK_LEN(o+l); vm.mem.data+o;})
# define GET_CHECKED_VAL(o, t) *(t*)({CHECK_LEN(o+sizeof(t)); vm.mem.data+o;})

#endif
