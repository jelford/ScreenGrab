Import(['env', 'sources', 'platform_libs', 'target_platform'])
env.Append(CCFLAGS = ['--std=c++0x', '-g'])
env.Append(CPPPATH = ['.', target_platform])

object_list = env.Object(source=sources)
t = Program(target='screengrab', source=object_list, LIBS = ['boost_system', 'boost_filesystem'] + platform_libs, )

Default(t)
