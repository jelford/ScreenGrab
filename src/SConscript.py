Import(['env', 'sources', 'cross_platform_libs', 'platform_libs', 'target_platform'])
env.Append(CPPPATH = ['.', target_platform])

object_list = env.Object(source=sources)
t = Program(target='screengrab', source=object_list, LIBS = cross_platform_libs + platform_libs, )

Default(t)
