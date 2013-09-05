/*
 * Created by ichiko on 2013/09/02
 */

package cc.clv.yamiHikariGame.gamecenter;

import android.app.Activity;
import android.content.Intent;
import android.util.Log;
import cc.clv.yamiHikariGame.yamiHikariGame;

import com.google.android.gms.games.GamesClient;
import com.google.android.gms.games.achievement.Achievement;
import com.google.android.gms.games.achievement.AchievementBuffer;
import com.google.android.gms.games.achievement.OnAchievementsLoadedListener;

public class GameCenter {

	private static GameHelper mGameHelper = null;
	private static final Activity activity = (Activity) yamiHikariGame
			.getContext();
	private static final String TAG = "yamiHikariGame.GameCenter";
	private static final int REQUEST_CODE_ACHIEVEMENT = 9010;
	private static final int REQUEST_CODE_LEADERBOARD = 9011;

	static class AchievementLoadedListenerForUpdate implements
			OnAchievementsLoadedListener {
		private GamesClient mGamesClient;
		private String mAchievementId;
		private int mProcess;

		/**
		 * 
		 * @param process
		 *            端末に保存された獲得済みカウント
		 */
		public AchievementLoadedListenerForUpdate(GamesClient client,
				String achievementId, int process) {
			mGamesClient = client;
			mAchievementId = achievementId;
			mProcess = process;
		}

		@Override
		public void onAchievementsLoaded(int statusCode,
				AchievementBuffer buffer) {
			if (statusCode == GamesClient.STATUS_OK) {
				int bufSize = buffer.getCount();
				for (int i = 0; i < bufSize; i++) {
					Achievement achievement = buffer.get(i);
					if (achievement != null
							&& achievement.getAchievementId().equals(
									mAchievementId)) {
						int steps = mProcess - achievement.getCurrentSteps();
						if (steps > 0) {
							mGamesClient.incrementAchievement(mAchievementId,
									steps);
						}
					}
				}
			}
		}

	}

	public static void onStart() {
		getGameHelper().onStart(activity);
	}

	public static void onStop() {
		getGameHelper().onStop();
	}

	public static void onActivityResult(int requestCode, int responseCode,
			Intent data) {
		if (mGameHelper == null) {
			return;
		}

		getGameHelper().onActivityResult(requestCode, responseCode, data);
	}

	public static void signIn() {
		activity.runOnUiThread(new Runnable() {
			public void run() {
				getGameHelper().beginUserInitiatedSignIn();
			}
		});
	}

	public static void signOut() {
		activity.runOnUiThread(new Runnable() {
			public void run() {
				getGameHelper().signOut();
			}
		});
	}

	public static boolean isSignedIn() {
		return mGameHelper != null && getGameHelper().isSignedIn();
	}

	public static boolean registerScore(final String leaderboardId,
			final int score) {
		if (!isSignedIn()) {
			return false;
		}

		activity.runOnUiThread(new Runnable() {
			public void run() {
				getGameHelper().getGamesClient().submitScore(leaderboardId,
						score);
			}
		});
		return true;
	}

	/**
	 * 
	 * @param achievementId
	 * @param process	進捗工数ではなく、これまでに獲得した全数
	 * @return
	 */
	public static boolean incrementAchievementDiffWithServerData(final String achievementId,
			final int process) {
		if (!isSignedIn()) {
			return false;
		}

		activity.runOnUiThread(new Runnable() {
			public void run() {
				// getGameHelper().getGamesClient().incrementAchievement(
				// achievementId, steps);
				getGameHelper().getGamesClient().loadAchievements(
						new AchievementLoadedListenerForUpdate(getGameHelper()
								.getGamesClient(), achievementId, process));
			}
		});
		return true;
	}
	
	public static boolean unlockAchievement(final String achievementId) {
		if (!isSignedIn()) {
			return false;
		}
		
		activity.runOnUiThread(new Runnable() {
			public void run() {
				getGameHelper().getGamesClient().unlockAchievement(achievementId);
			}
		});
		return true;
	}

	public static boolean showLeaderboard() {
		if (!isSignedIn()) {
			return false;
		}

		activity.runOnUiThread(new Runnable() {
			public void run() {
				activity.startActivityForResult(getGameHelper()
						.getGamesClient().getAllLeaderboardsIntent(),
						REQUEST_CODE_LEADERBOARD);
			}
		});
		return true;
	}

	public static boolean showAchievements() {
		if (!isSignedIn()) {
			return false;
		}

		activity.runOnUiThread(new Runnable() {
			public void run() {
				activity.startActivityForResult(getGameHelper()
						.getGamesClient().getAchievementsIntent(),
						REQUEST_CODE_ACHIEVEMENT);
			}
		});
		return true;
	}

	private static GameHelper getGameHelper() {
		if (mGameHelper == null) {
			mGameHelper = new GameHelper(activity);
			mGameHelper.enableDebugLog(true, TAG);

			activity.runOnUiThread(new Runnable() {
				public void run() {
					mGameHelper.setup(new GameHelper.GameHelperListener() {

						@Override
						public void onSignInSucceeded() {
							Log.v(TAG, "onSignInSucceeded");
						}

						@Override
						public void onSignInFailed() {
							Log.v(TAG, "onSignInFailed");
						}
					}, GameHelper.CLIENT_GAMES);
				}
			});
		}
		return mGameHelper;
	}

}
