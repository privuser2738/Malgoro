# Contributing to Malgoro

Thank you for your interest in contributing to Malgoro! This document provides guidelines for contributing to the project.

## Code of Conduct

- Be respectful and inclusive
- Welcome newcomers and help them get started
- Focus on constructive feedback
- Maintain professional communication

## Getting Started

### Setting Up Development Environment

1. Fork the repository on GitHub
2. Clone your fork:
   ```bash
   git clone https://github.com/YOUR_USERNAME/malgoro.git
   cd malgoro
   ```

3. Add upstream remote:
   ```bash
   git remote add upstream https://github.com/privuser2738/malgoro.git
   ```

4. Install dependencies (Manjaro/Arch):
   ```bash
   sudo pacman -S gcc cmake libgit2 sqlite openssl gtk3 pkg-config
   ```

5. Build the project:
   ```bash
   cd MalgoroPkg
   mkdir build && cd build
   cmake -DCMAKE_BUILD_TYPE=Debug ..
   make
   ```

## Development Workflow

### Branching Strategy

- `main` - Stable releases
- `develop` - Integration branch for features
- `feature/*` - New features
- `bugfix/*` - Bug fixes
- `hotfix/*` - Urgent production fixes

### Making Changes

1. Create a feature branch:
   ```bash
   git checkout -b feature/my-feature develop
   ```

2. Make your changes following our coding standards

3. Test your changes thoroughly

4. Commit with descriptive messages:
   ```bash
   git commit -m "Add feature: description of what you did"
   ```

5. Push to your fork:
   ```bash
   git push origin feature/my-feature
   ```

6. Create a Pull Request on GitHub

## Coding Standards

### C++ Guidelines

- **Standard**: Use C++20 features
- **Style**: Follow Google C++ Style Guide
- **Naming**:
  - Classes: `PascalCase`
  - Functions/Methods: `snake_case`
  - Variables: `snake_case`
  - Constants: `UPPER_CASE`
  - Private members: `trailing_underscore_`

- **Headers**:
  - Use include guards: `#ifndef MALGORO_FILENAME_H`
  - Group includes: system, third-party, project
  - Forward declare when possible

### Example Code Style

```cpp
#ifndef MALGORO_EXAMPLE_H
#define MALGORO_EXAMPLE_H

#include <string>
#include <vector>

namespace Malgoro {

class ExampleClass {
public:
    ExampleClass(const std::string& name);
    ~ExampleClass();

    bool process_data(const std::vector<int>& data);
    std::string get_name() const;

private:
    std::string name_;
    int counter_;

    void internal_helper();
};

} // namespace Malgoro

#endif // MALGORO_EXAMPLE_H
```

### Error Handling

- Use exceptions for exceptional cases
- Return `std::optional` for operations that may fail
- Log errors using the Logger system
- Provide meaningful error messages

```cpp
std::optional<Package> find_package(const std::string& name) {
    auto result = search_database(name);
    if (!result) {
        LOG_WARNING("Package not found: " + name);
        return std::nullopt;
    }
    return result;
}
```

### Memory Management

- Use smart pointers (`std::unique_ptr`, `std::shared_ptr`)
- Follow RAII principles
- Avoid raw `new` and `delete`
- Use standard containers

### Logging

Use the logging macros throughout the code:

```cpp
LOG_DEBUG("Detailed debug information");
LOG_INFO("General information");
LOG_WARNING("Warning about potential issues");
LOG_ERROR("Error occurred");
LOG_FATAL("Critical failure");
```

## Testing

### Writing Tests

- Add tests for all new features
- Test both success and failure cases
- Use descriptive test names

### Running Tests

```bash
cd build
make test
```

## Documentation

### Code Documentation

Use Doxygen-style comments:

```cpp
/**
 * @brief Install a package and its dependencies
 *
 * @param package_name Name of the package to install
 * @param resolve_deps Whether to install dependencies
 * @return InstallStatus indicating success or failure reason
 */
InstallStatus install(const std::string& package_name, bool resolve_deps = true);
```

### Documentation Files

Update relevant documentation when making changes:

- `README.md` - Project overview
- `MalgoroPkg/README.md` - Package manager docs
- `docs/PACKAGE_CREATION.md` - Package creation guide
- `CONTRIBUTING.md` - This file

## Commit Messages

### Format

```
<type>(<scope>): <subject>

<body>

<footer>
```

### Types

- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation changes
- `style`: Code style changes (formatting)
- `refactor`: Code refactoring
- `test`: Adding or updating tests
- `chore`: Maintenance tasks

### Examples

```
feat(package-manager): Add parallel repository synchronization

Implement concurrent repository syncing using thread pool to improve
performance when working with multiple repositories.

Closes #123
```

```
fix(database): Prevent SQL injection in package queries

Use prepared statements for all database queries to prevent
potential SQL injection vulnerabilities.

Security: CVE-2024-XXXXX
```

## Pull Request Process

1. **Update documentation** - Keep docs in sync with code changes

2. **Add tests** - Ensure new code is tested

3. **Run tests locally** - All tests must pass

4. **Update CHANGELOG** - Document your changes

5. **Fill PR template** - Describe what and why

6. **Request review** - Tag relevant maintainers

7. **Address feedback** - Make requested changes

8. **Squash commits** - Clean up commit history if requested

## Review Criteria

Pull requests are reviewed for:

- **Functionality** - Does it work as intended?
- **Code quality** - Follows coding standards?
- **Tests** - Adequate test coverage?
- **Documentation** - Is it documented?
- **Performance** - No performance regressions?
- **Security** - No security vulnerabilities?

## Reporting Issues

### Bug Reports

Include:
- Malgoro version
- Operating system and version
- Steps to reproduce
- Expected vs actual behavior
- Relevant logs
- Screenshots if applicable

### Feature Requests

Include:
- Clear description of the feature
- Use cases and examples
- Potential implementation approach
- Willingness to contribute

## Types of Contributions

### Code Contributions

- Bug fixes
- New features
- Performance improvements
- Refactoring

### Non-Code Contributions

- Documentation improvements
- Translation
- Package creation
- Testing and bug reporting
- Community support

## Desktop Environment Development

When contributing to MalgoroDE:

- Follow GTK+ best practices
- Test on multiple screen sizes
- Ensure accessibility
- Maintain the classic aesthetic
- Test with common applications

## Package Repository Contributions

To contribute packages:

1. Create packages following `docs/PACKAGE_CREATION.md`
2. Test thoroughly
3. Submit to community repository
4. Maintain your packages

## Community

### Communication Channels

- GitHub Issues - Bug reports and features
- GitHub Discussions - General questions
- [Future: Discord/IRC/Matrix]

### Getting Help

- Check existing documentation
- Search closed issues
- Ask in discussions
- Tag maintainers for urgent issues

## Recognition

Contributors are recognized in:
- CONTRIBUTORS.md file
- Release notes
- Project website (future)

## License

By contributing, you agree that your contributions will be licensed under the same license as the project (GPL-3.0).

## Questions?

If you have questions about contributing, please:
1. Check this document
2. Search existing issues
3. Open a new discussion
4. Contact maintainers

Thank you for contributing to Malgoro!
