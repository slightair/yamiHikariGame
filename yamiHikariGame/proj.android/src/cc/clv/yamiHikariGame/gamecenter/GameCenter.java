/*
 * Created by ichiko on 2013/09/02
 */

package cc.clv.yamiHikariGame.gamecenter;

import java.util.HashMap;
import java.util.Map;

import android.app.Activity;
import android.content.Intent;
import android.util.Log;
import cc.clv.yamiHikariGame.yamiHikariGame;
import cc.clv.yamiHikariGame.gamecenter.GameHelper.GameHelperListener;

import com.google.android.gms.games.GamesClient;
import com.google.android.gms.games.achievement.Achievement;
import com.google.android.gms.games.achievement.AchievementBuffer;
import com.google.android.gms.games.achievement.OnAchievementsLoadedListener;

public class GameCenter {

	private static GameHelper mGameHelper = null;
	private static Map<String, Achievement> serverAchievementStates = null;
	private static final Activity activity = (Activity) yamiHikariGame
			.getContext();
	private static final String TAG = "yamiHikariGame.GameCenter";
	private static final int REQUEST_CODE_ACHIEVEMENT = 9010;
	private static final int REQUEST_CODE_LEADERBOARD = 9011;
	private static final boolean enableDebug = false;

	static class GameCenterListener implements GameHelperListener {

		@Override
		public void onSignInFailed() {
			debugLog("onSignInFailed");
		}

		@Override
		public void onSignInSucceeded() {
			debugLog("onSignInSucceeded");
			GameCenter.loadInitialAchievementState();
		}

	}

	public static void onCreate() {
		if (mGameHelper == null) {
			setup();
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
				serverAchievementStates = null;
				getGameHelper().signOut();
			}
		});
	}

	public static boolean isSignedIn() {
		return mGameHelper != null && getGameHelper().isSignedIn();
	}

	/**
	 * ある時点の実績状態をすべて取得し、実績計算に使用する準備する
	 */
	private static void loadInitialAchievementState() {
		if (!isSignedIn()) {
			debugLog("Not Signed In : loadInitialAchievementState");
			return;
		}

		activity.runOnUiThread(new Runnable() {
			public void run() {
				getGameHelper().getGamesClient().loadAchievements(
						new OnAchievementsLoadedListener() {
							@Override
							public void onAchievementsLoaded(int statusCode,
									AchievementBuffer buffer) {
								if (serverAchievementStates == null
										&& statusCode == GamesClient.STATUS_OK) {
									serverAchievementStates = new HashMap<String, Achievement>();
									for (int i = 0; i < buffer.getCount(); i++) {
										Achievement achievement = buffer.get(i);
										serverAchievementStates.put(
												achievement.getAchievementId(),
												achievement);
									}
								}
							}

						});
			}
		});
	}

	public static boolean registerScore(final String leaderboardId,
			final int score) {
		if (!isSignedIn()) {
			debugLog("Not Signed In : registerScore");
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
	 *            実績ID
	 * @param process
	 *            進捗工数ではなく、これまでに獲得した全数
	 * @return
	 */
	public static boolean registerAchievement(final String achievementId,
			int process) {
		if (!isSignedIn()) {
			debugLog("Not Signed In : incrementAchievementDiffWithServerData");
			return false;
		}

		if (serverAchievementStates == null) {
			Log.w(TAG, "achievement status is not availabled. : increment");
		}

		if (serverAchievementStates.containsKey(achievementId)) {
			Achievement achievementInfo = serverAchievementStates
					.get(achievementId);

			if (achievementInfo.getState() == Achievement.STATE_UNLOCKED) {
				return false;
			}

			if (achievementInfo.getType() == Achievement.TYPE_INCREMENTAL) {
				int curretSteps = achievementInfo.getCurrentSteps();
				final int increment = process - curretSteps;

				if (increment > 0) {
					activity.runOnUiThread(new Runnable() {
						public void run() {
							getGameHelper().getGamesClient()
									.incrementAchievement(achievementId,
											increment);
						}
					});
				}
			}
			else {
				activity.runOnUiThread(new Runnable() {
					public void run() {
						getGameHelper().getGamesClient().unlockAchievement(achievementId);
					}
				});
			}
		}

		return true;
	}

	public static boolean showLeaderboard(final String leaderboardId) {
		if (!isSignedIn()) {
			debugLog("Not Signed In : showLeaderboard");
			return false;
		}

		activity.runOnUiThread(new Runnable() {
			public void run() {
				activity.startActivityForResult(getGameHelper()
						.getGamesClient().getLeaderboardIntent(leaderboardId),
						REQUEST_CODE_LEADERBOARD);
			}
		});
		return true;
	}

	public static boolean showAchievements() {
		if (!isSignedIn()) {
			debugLog("Not Signed In : showAchievements");
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

	private static void setup() {
		if (mGameHelper == null) {
			mGameHelper = new GameHelper(activity);
			if (enableDebug) {
				mGameHelper.enableDebugLog(true, TAG);
			}

			mGameHelper
					.setup(new GameCenterListener(), GameHelper.CLIENT_GAMES);
		}
	}

	private static GameHelper getGameHelper() {
		if (mGameHelper == null) {
			String msg = "Utility is not configured. Please call onCreate.";
			Log.e(TAG, msg);
			throw new IllegalStateException(msg);
		}

		return mGameHelper;
	}

	private static void debugLog(String msg) {
		if (enableDebug) {
			Log.v(TAG, msg);
		}
	}
}
