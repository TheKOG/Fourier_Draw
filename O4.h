%:pragma GCC optimize(3)
%:pragma GCC optimize("Ofast")
%:pragma GCC optimize("inline")
%:pragma GCC optimize("-fgcse")
%:pragma GCC optimize("-fgcse-lm")
%:pragma GCC optimize("-fipa-sra")
%:pragma GCC optimize("-ftree-pre")
%:pragma GCC optimize("-ftree-vrp")
%:pragma GCC optimize("-fpeephole2")
%:pragma GCC optimize("-ffast-math")
%:pragma GCC optimize("-fsched-spec")
%:pragma GCC optimize("unroll-loops")
%:pragma GCC optimize("-falign-jumps")
%:pragma GCC optimize("-falign-loops")
%:pragma GCC optimize("-falign-labels")
%:pragma GCC optimize("-fdevirtualize")
%:pragma GCC optimize("-fcaller-saves")
%:pragma GCC optimize("-fcrossjumping")
%:pragma GCC optimize("-fthread-jumps")
%:pragma GCC optimize("-funroll-loops")
%:pragma GCC optimize("-fwhole-program")
%:pragma GCC optimize("-freorder-blocks")
%:pragma GCC optimize("-fschedule-insns")
%:pragma GCC optimize("inline-functions")
%:pragma GCC optimize("-ftree-tail-merge")
%:pragma GCC optimize("-fschedule-insns2")
%:pragma GCC optimize("-fstrict-aliasing")
%:pragma GCC optimize("-fstrict-overflow")
%:pragma GCC optimize("-falign-functions")
%:pragma GCC optimize("-fcse-skip-blocks")
%:pragma GCC optimize("-fcse-follow-jumps")
%:pragma GCC optimize("-fsched-interblock")
%:pragma GCC optimize("-fpartial-inlining")
%:pragma GCC optimize("no-stack-protector")
%:pragma GCC optimize("-freorder-functions")
%:pragma GCC optimize("-findirect-inlining")
%:pragma GCC optimize("-fhoist-adjacent-loads")
%:pragma GCC optimize("-frerun-cse-after-loop")
%:pragma GCC optimize("inline-small-functions")
%:pragma GCC optimize("-finline-small-functions")
%:pragma GCC optimize("-ftree-switch-conversion")
%:pragma GCC optimize("-foptimize-sibling-calls")
%:pragma GCC optimize("-fexpensive-optimizations")
%:pragma GCC optimize("-funsafe-loop-optimizations")
%:pragma GCC optimize("inline-functions-called-once")
%:pragma GCC optimize("-fdelete-null-pointer-checks")
/*
����������������������������������������������������������������������������������
����������������������������������������������������������������������������������
�����������������������������������۷��������۹�����������������������������������
�����������������������������۷��������۷��������۷�������������������������������
�������������������������������۾۾۾۾۾۾۾۾۾۾۷��۹�������������������������
�����������������������������۾۾۾۾��������������۾����۹�����������������������
�����������������������������۾۾��������Ĺ����Ĺ������۾��۹����������Ĺ���������
�������������������������۾۾������������������ľ��Ĺ����۾��������������������ġ�
�������������������ķ��۾۾��������������ľþþþþ����ľ��۾������������������ġ�
�����������������ķ������۹������������ľþþþþþþ��Ĺ����۷����������������ġ�
�����������������ķ����������������������ľþþþþþ����ľ��۷����������������ġ�
�����������������ķ������۾��������������ľþþþþþþ��Ĺ��۷����������������ġ�
���������������Ĺ��������۾����������ľþþ��ľþþþþ��Ĺ��۷����������������ġ�
�����������������ķ������۾��۾��������ľþ��ľþþþ����Ĺ��۷����������������ġ�
�����������������ķ������۾����۾����۹��ľ����Ĺ��������Ĺ������þþþþ������ġ�
�������������ľþþ۷��������������Ĺ��÷��ľ۹����ľþ÷������ľþþþþþþþá�
���ľþþþþþþþ۾۾۾۷��۾۾۷��۾��۷��ľ��۾۾����Ĺ��۾þþþþþþþþá�
�þþþþþþþþþ۾��۾��������������������Ĺ��ľþ������Ĺ��þþþþþþþþá�
�þþþþþþþþþ����۾��������Ĺ��ľ۾��÷��Ĺ������ľ��Ĺ��þþþþþþþþá�
�þþþþþþþþþþ۾������������Ĺ������þ��Ĺ��ľþþ��ľþþþþþþþþþá�
�þþþþþþþþþþ��۾۾۾������۾۹����ľù������������ľþþþþþþþþþá�
�þþþþþþþþþþ����۾۾����Ĺ��۷��۾��������������ľ�ʮʮʮʮʮʮʮʮʮʮ��
�þþþþ�ʮʮʮʮʮ�����۾۾۾������������þþþ��Ĺ����ľ�ʮʮʮʮʮʮʮʮʮʮ��
�þ�ʮʮʮʮʮʮʮʮ�þ۾۾۾۹������������ľþ��Ĺ������ľ�ʮʮʮʮʮʮʮʮʮʮ��
ʮʮʮʮʮʮʮʮʮʮʮ���۾۾��ľ۾۾۾�������������������ʮʮʮʮʮʮʮʮʮʮʮ��
ʮʮʮʮʮʮʮʮʮʮʮ���۾۾۹����۾������ľþþ���������ʮʮʮʮʮʮʮʮʮʮʮ��
ʮʮʮʮʮʮʮʮʮʮʮ�ľ��۾۾������������ľþþ�������ʮʮʮʮʮʮʮʮʮʮʮʮ��
ʮʮʮʮʮʮʮʮʮʮʮ���۾۾۾۹������������ľþ��Ĺ���ʮʮʮʮʮʮʮʮʮʮʮʮ��
ʮʮʮʮʮʮʮʮʮʮʮ�����۾۾۾۹��������ľþ��Ĺ�����������������������ʮ��ʮ��
ʮʮʮʮʮʮ���������������۾��۾۾۾����������Ĺ����ģ���������������������������
����ʮ�������������������������۾۾۾۾۾۾۾۾������ģ���������������������������
�������������������������������ľ۾۾۾۾۾��������þ۷����ۣ���������������������
������ʮ���������������������������ľ����۾������ģ��۷���������������������������
��ʮ�������������������������������ľþù����ľá����۾۷������������ۣ�����������
����������������������������������ʮʮ�����۾������������������������������ģ�����
����������������������������������ʮ�þ��������������۷������������������������á�
�����������������������������������۹������۾��۾����۾۷����������������������ۡ�
������������������������������������ʮ�����۹������ľ۷������������������۷�������
�������������������������������������۹������۹������ľ۷��۷������������������ۡ�
��������������������������������������ʮ�����۾ۣ����������������������������۾ۡ�
����������������������������������������������������������������������������������
*/