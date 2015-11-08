
myShopClientps.dll: dlldata.obj myShopClient_p.obj myShopClient_i.obj
	link /dll /out:myShopClientps.dll /def:myShopClientps.def /entry:DllMain dlldata.obj myShopClient_p.obj myShopClient_i.obj \
		kernel32.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \
.c.obj:
	cl /c /Ox /DREGISTER_PROXY_DLL \
		$<

clean:
	@del myShopClientps.dll
	@del myShopClientps.lib
	@del myShopClientps.exp
	@del dlldata.obj
	@del myShopClient_p.obj
	@del myShopClient_i.obj
