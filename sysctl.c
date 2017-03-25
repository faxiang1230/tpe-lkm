
#include "module.h"

int tpe_softmode = 0;
int tpe_trusted_gid = 0;
int tpe_trusted_invert = 0;
int tpe_admin_gid = 0;
int tpe_dmz_gid = 0;
int tpe_strict = 1;
int tpe_check_file = 1;
int tpe_group_writable = 1;
int tpe_paranoid = 0;
char tpe_trusted_apps[TPE_PATH_LEN] = "";
char tpe_hardcoded_path[TPE_PATH_LEN] = "";
int tpe_kill = 0;
int tpe_log = 1;
int tpe_log_max = 50;
int tpe_log_floodtime = LOG_FLOODTIME;
int tpe_log_floodburst = LOG_FLOODBURST;

int tpe_lsmod = 1;
int tpe_proc_kallsyms = 1;
int tpe_harden_ptrace = 1;
int tpe_hide_uname = 0;

static ctl_table tpe_table[] = {
	{
		.procname	= "softmode",
		.data		= &tpe_softmode,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec,
	},
	{
		.procname	= "trusted_gid",
		.data		= &tpe_trusted_gid,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec,
	},
	{
		.procname	= "trusted_invert",
		.data		= &tpe_trusted_invert,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec,
	},
	{
		.procname	= "admin_gid",
		.data		= &tpe_admin_gid,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec,
	},
	{
		.procname	= "dmz_gid",
		.data		= &tpe_dmz_gid,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec,
	},
	{
		.procname	= "strict",
		.data		= &tpe_strict,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec,
	},
	{
		.procname	= "check_file",
		.data		= &tpe_check_file,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec,
	},
	{
		.procname	= "group_writable",
		.data		= &tpe_group_writable,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec,
	},
	{
		.procname	= "paranoid",
		.data		= &tpe_paranoid,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec,
	},
        {
                .procname       = "trusted_apps",
                .data           = &tpe_trusted_apps,
                .maxlen         = TPE_PATH_LEN,
                .mode           = 0644,
                .proc_handler   = &proc_dostring,
        },
        {
                .procname       = "hardcoded_path",
                .data           = &tpe_hardcoded_path,
                .maxlen         = TPE_PATH_LEN,
                .mode           = 0644,
                .proc_handler   = &proc_dostring,
        },
	{
		.procname	= "kill",
		.data		= &tpe_kill,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec,
	},
	{
		.procname	= "log",
		.data		= &tpe_log,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec,
	},
	{
		.procname	= "log_max",
		.data		= &tpe_log_max,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec,
	},
	{
		.procname	= "log_floodtime",
		.data		= &tpe_log_floodtime,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec,
	},
	{
		.procname	= "log_floodburst",
		.data		= &tpe_log_floodburst,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec,
	},
	{0}
};

static ctl_table tpe_root_table[] = {
	{
		.procname	= MODULE_NAME,
		.mode		= 0500,
		.child		= tpe_table,
	},
	{0}
};

static struct ctl_table_header *tpe_table_header;

int tpe_config_init(void) {
	if (!(tpe_table_header = register_sysctl_table(tpe_root_table))) {
		printk(PKPRE "Unable to register sysctl table with the kernel\n");
		return -EFAULT;
	}

	return 0;
}

void tpe_config_exit(void) {

	if (tpe_table_header)
		unregister_sysctl_table(tpe_table_header);

}

