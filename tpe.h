#ifndef TPE_H_INCLUDED
#define TPE_H_INCLUDED

#include <linux/module.h>
#include <linux/file.h>
#include <linux/mman.h>
#include <linux/binfmts.h>
#include <linux/cred.h>
#include <linux/xattr.h>
#include <linux/fs.h>
#include <linux/jiffies.h>
#include <linux/sysctl.h>
#include <linux/version.h>

#define PKPRE "tpe: "
#define MAX_FILE_LEN 255
#define TPE_PATH_LEN 1024

#define TPE_LOG_FLOODTIME 5
#define TPE_LOG_FLOODBURST 5

#define IN_ERR(x) (x < 0)

#define get_task_uid(task) __kuid_val(task->cred->uid)
#define get_task_parent(task) task->real_parent

#define tpe_d_path(file, buf, len) d_path(&file->f_path, buf, len);

#define get_dentry(file) file->f_path.dentry
#define get_inode(file) get_dentry(file)->d_inode
#define get_parent_inode(file) file->f_path.dentry->d_parent->d_inode;
#define exe_from_mm(mm, buf, len) tpe_d_path(mm->exe_file, buf, len)

#define UID_IS_TRUSTED(uid) \
	((uid == 0 && !tpe_paranoid) || \
	(!tpe_trusted_invert && tpe_trusted_gid && in_group_p(KGIDT_INIT(tpe_trusted_gid)) && !tpe_strict) || \
	(tpe_trusted_invert && !in_group_p(KGIDT_INIT(tpe_trusted_gid))))

#define INODE_IS_WRITABLE(inode) ((inode->i_mode & S_IWOTH) || (tpe_group_writable && inode->i_mode & S_IWGRP))
#define INODE_IS_TRUSTED(inode) \
	(__kuid_val(inode->i_uid) == 0 || \
	(tpe_admin_gid && __kgid_val(inode->i_gid) == tpe_admin_gid) || \
	(__kuid_val(inode->i_uid) == get_task_uid(current) && !tpe_trusted_invert && tpe_trusted_gid && in_group_p(KGIDT_INIT(tpe_trusted_gid))))

/* tpe prototypes */
int tpe_allow_file(const struct file *, const char *);
int tpe_file_getfattr(const struct file *, const char *);
int tpe_log_denied_action(const struct file *, const char *, const char *, int, int);
int tpe_config_init(void);
void tpe_config_exit(void);

/* sysctl entries for configuration */
extern int tpe_softmode;
extern int tpe_xattr_soften;
extern int tpe_trusted_gid;
extern int tpe_trusted_invert;
extern int tpe_admin_gid;
extern int tpe_dmz_gid;
extern int tpe_strict;
extern int tpe_check_file;
extern int tpe_group_writable;
extern int tpe_paranoid;
extern char tpe_trusted_apps[];
extern char tpe_hardcoded_path[];
extern int tpe_kill;
extern int tpe_log;
extern int tpe_log_verbose;
extern int tpe_log_max;
extern int tpe_log_floodtime;
extern int tpe_log_floodburst;
extern int tpe_lock;
extern int tpe_lsmod;
extern int tpe_proc_kallsyms;
extern int tpe_harden_ptrace;
extern int tpe_hide_uname;
extern int tpe_extras_ignore_softmode;
extern int tpe_extras_log;
extern int tpe_ps;
extern int tpe_ps_gid;
extern int tpe_restrict_setuid;

#endif
