# Contribution Guidelines

This library is a wrapper library for the [Adafruit/NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel). This library is an auxilary liibrary and is intended to be installed along with Adafruit's library, **not as an individual library**.

## Contributors 

There are broadly three different levels of contributors.

| Role | Description |
| ---- | ----------- |
| Core member | Code owner and reviewer |
| Volunteer | Directly affiliated code contributor |
| Open Source Contributor | Non-affiliated general contributor |

Core member and Volunteer roles are assigned internally at Code Wth Her. Open Source Contributors are for the general public.

## Contributing

All contributors are invited to submit issues for the following:
- Bugs
- Feature Requests
- Discussion

## Contributing to issues

In order to ensure we're progressing in methodically, code shoud only be contributed to existing issues or issues should created which will in turn be added to the project timeline, tabled to the backlog, or dismissed.

- [Accepted Project Timeline](https://github.com/orgs/codewithher/projects/2)
- We will be following a 2 week sprint cycle
- Assignments will be handled explicitly via meetings or email

## Contributing pull requests

When contributing to the repo, please insure that:
- The PR resolves at least one existing/documented issue
    - Include issue number by linking the `#XXX` in the description
- Write small PRs that handle specific topics
- Format commit messages with readability in mind
    - Start with an action verb like "Fix" or "Add"

## Git Branching Strategy

We incorporate a modified [GitHub flow](https://docs.github.com/en/get-started/using-github/github-flow) branching strategy. 

Each feature has an overarching branch that is prefixed with `<issue number>-feature-<feature_name>` which then has subsequent branches implementing parts of that feature. The intention is to make small PRs that are easier to [conduct code review](https://www.youtube.com/watch?v=-4b3OSwuLM8) for. See the attached image example for more details.

![Branching Strategy](./docs/assets/branching.png)
[Branching Strategy](https://excalidraw.com/#json=a5Nm80xPT2uzbYwdAoNp4,Yggmz2D6xa9LTu0WR1loQw)

## Git Versioning Semantics

Git Version Tags / Release Tags are required to be accepted into the Arduino Registry. The current version should be reflected in [library.properties](/library.properties)

Each new PR should increment the current release version in the following format `version.feature.patch`:
- `1.0.0` for full new versions that has major rewrites in the corresponding instruction material
- `0.1.0` for new features or activities
- `0.0.1` for bug patches or fixes

When the release version is incremented, any numbers to the right are reset to 0.

- Ex: New major version: `0.2.0` -> `1.0.0`
  - Version `0 -> 1`
  - Feature `2 -> 0`
  - Patch `0 -> 0`
- Ex: New feature: `4.8.2` ->  `4.9.0`
  - Version `4`
  - Feature `8 -> 9`
  - Patch `2 -> 0`
- Ex: New patch: `5.4.22` -> `5.4.23`
  - Version `5`
  - Feature `4`
  - Patch `22 -> 23`

## FAQ

If you have any questions or concerns, contact ryan@codewithher.org.

- **Not familar with git/version control?**  
  - I recommend following [GitHub/Skills](https://skills.github.com/) tutorials.
- **Not familiar with markdown?**
  - Make sure you use the "preview" feature instead of spamming commits
  - Do a quick scan of [Markdownguide](https://www.markdownguide.org/cheat-sheet/)
  - Look at the code view of existing issues or PRs
