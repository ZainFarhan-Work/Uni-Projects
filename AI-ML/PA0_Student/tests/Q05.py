OK_FORMAT = True

test = {   'name': 'Q05',
    'points': 1,
    'suites': [   {   'cases': [   {   'code': '>>> assert x.shape == (20,)\n'
                                               '>>> assert y.shape == (20,)\n'
                                               '>>> assert z.shape == (20,)\n'
                                               '>>> assert np.all(x >= 1) and np.all(x <= 10)\n'
                                               '>>> assert np.all(y >= 1) and np.all(y <= 10)\n'
                                               '>>> assert z[0] == (x[0] + y[0]) ** 2\n',
                                       'hidden': False,
                                       'locked': False}],
                      'scored': True,
                      'setup': '',
                      'teardown': '',
                      'type': 'doctest'}]}
