import { SetupPage } from './app.po';

describe('setup App', () => {
  let page: SetupPage;

  beforeEach(() => {
    page = new SetupPage();
  });

  it('should display message saying app works', () => {
    page.navigateTo();
    expect(page.getParagraphText()).toEqual('app works!');
  });
});
