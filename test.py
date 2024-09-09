# import json
# import numpy as np
# from sklearn.preprocessing import StandardScaler
# from sklearn.ensemble import RandomForestClassifier
# import joblib
#
# def calculate_direction_change(hed_x, hed_y):
#     changes = []
#     for i in range(1, len(hed_x)):
#         dot_product = np.dot([hed_x[i - 1], hed_y[i - 1]], [hed_x[i], hed_y[i]])
#         norms_product = np.linalg.norm([hed_x[i - 1], hed_y[i - 1]]) * np.linalg.norm([hed_x[i], hed_y[i]])
#         dot_product = max(min(dot_product / norms_product, 1), -1)
#         change = np.arccos(dot_product)
#         changes.append(np.degrees(change))
#     return changes if changes else [0]
#
# def extract_features(data):
#     if not data:
#         return None  # No data to process, avoid NaN generation
#
#     send_times = [d['sendTime'] for d in data]
#     send_time_diffs = [send_times[i] - send_times[i - 1] for i in range(1, len(send_times))]
#     non_integer_diffs_fraction = np.mean([not np.isclose(diff, round(diff), atol=2e-4) for diff in send_time_diffs]) if send_time_diffs else 0
#
#     acl_x, acl_y, hed_x, hed_y, spd, msg_ids = zip(*[(d['acl'][0], d['acl'][1], d['hed'][0], d['hed'][1], np.linalg.norm(d['spd']), d['messageID']) for d in data])
#     dir_changes = calculate_direction_change(hed_x, hed_y)
#     mean_dir_change = np.mean(dir_changes) if dir_changes else 0
#     max_dir_change = np.max(dir_changes) if dir_changes else 0
#     var_dir_change = np.var(dir_changes) if dir_changes else 0
#
#     pos_ratio_x = np.sum(np.array(acl_x) > 0) / (np.sum(np.array(acl_x) < 0) + 1e-5) if np.sum(np.array(acl_x) < 0) != 0 else 0
#     pos_ratio_y = np.sum(np.array(acl_y) > 0) / (np.sum(np.array(acl_y) < 0) + 1e-5) if np.sum(np.array(acl_y) < 0) != 0 else 0
#     dispersion = np.var(acl_x) + np.var(acl_y)
#     var_x = np.var(acl_x)
#     var_y = np.var(acl_y)
#     mean_acl_x = np.mean(acl_x)
#     mean_acl_y = np.mean(acl_y)
#     mean_spd = np.mean(spd)
#     var_spd = np.var(spd)
#     msg_id_diff_sum = np.sum(np.diff(msg_ids)) if msg_ids and len(msg_ids) > 1 else 0
#
#     features = [pos_ratio_x, pos_ratio_y, dispersion, var_x, var_y, mean_acl_x, mean_acl_y, mean_spd, var_spd,
#                 mean_dir_change, max_dir_change, var_dir_change, msg_id_diff_sum, non_integer_diffs_fraction]
#     return [0 if np.isnan(x) else x for x in features]  # Replace NaN with 0
#
# def load_model(model_path, scaler_path):
#     model = joblib.load(model_path)
#     scaler = joblib.load(scaler_path)
#     return model, scaler
#
# def classify_data(data, model, scaler):
#     features = extract_features(data)
#     if features is None:
#         return "Invalid or insufficient data"
#     features_scaled = scaler.transform([features])
#     return model.predict(features_scaled)
#
# def main():
#     model_path = './model/trained_model.joblib'
#     scaler_path = './model/scaler.joblib'
#     model, scaler = load_model(model_path, scaler_path)
#
#     data_path = './test/traceJSON-2241-2239-A0-18525-0.json'
#     data_buffer = []
#     pseudo_count = {}
#
#     with open(data_path, 'r') as file:
#         for line in file:
#             data = json.loads(line)
#             sender_pseudo = data['senderPseudo']
#
#             if sender_pseudo not in pseudo_count:
#                 pseudo_count[sender_pseudo] = 0
#
#             if pseudo_count[sender_pseudo] < 5:
#                 data_buffer.append(data)
#                 pseudo_count[sender_pseudo] += 1
#
#                 if pseudo_count[sender_pseudo] == 5:
#                     label = classify_data(data_buffer, model, scaler)
#                     print(f"Data batch with senderPseudo {sender_pseudo} classified as {label}")
#                     data_buffer = []  # Reset the buffer
#                     pseudo_count[sender_pseudo] = 0
#
# if __name__ == "__main__":
#     main()

# import json
# import numpy as np
# from sklearn.preprocessing import StandardScaler
# from sklearn.ensemble import RandomForestClassifier
# import joblib
#
# def calculate_direction_change(hed_x, hed_y):
#     changes = []
#     for i in range(1, len(hed_x)):
#         dot_product = np.dot([hed_x[i - 1], hed_y[i - 1]], [hed_x[i], hed_y[i]])
#         norms_product = np.linalg.norm([hed_x[i - 1], hed_y[i - 1]]) * np.linalg.norm([hed_x[i], hed_y[i]])
#         dot_product = max(min(dot_product / norms_product, 1), -1)
#         change = np.arccos(dot_product)
#         changes.append(np.degrees(change))
#     return changes if changes else [0]
#
# def extract_features(data):
#     send_times = [d['sendTime'] for d in data]
#     send_time_diffs = [send_times[i] - send_times[i - 1] for i in range(1, len(send_times))]
#     non_integer_diffs_fraction = np.mean([not np.isclose(diff, round(diff), atol=2e-4) for diff in send_time_diffs])
#     acl_x, acl_y, hed_x, hed_y, spd, msg_ids = zip(
#         *[(d['acl'][0], d['acl'][1], d['hed'][0], d['hed'][1], np.linalg.norm(d['spd']), d['messageID']) for d in data])
#     dir_changes = calculate_direction_change(hed_x, hed_y)
#     mean_dir_change = np.mean(dir_changes) if dir_changes else 0
#     max_dir_change = np.max(dir_changes) if dir_changes else 0
#     var_dir_change = np.var(dir_changes) if dir_changes else 0
#     pos_ratio_x = np.sum(np.array(acl_x) > 0) / (np.sum(np.array(acl_x) < 0) + 1e-5)
#     pos_ratio_y = np.sum(np.array(acl_y) > 0) / (np.sum(np.array(acl_y) < 0) + 1e-5)
#     dispersion = np.var(acl_x) + np.var(acl_y)
#     var_x = np.var(acl_x)
#     var_y = np.var(acl_y)
#     mean_acl_x = np.mean(acl_x)
#     mean_acl_y = np.mean(acl_y)
#     mean_spd = np.mean(spd)
#     var_spd = np.var(spd)
#     msg_id_diff_sum = np.sum(np.diff(msg_ids))
#     return [pos_ratio_x, pos_ratio_y, dispersion, var_x, var_y, mean_acl_x, mean_acl_y, mean_spd, var_spd,
#             mean_dir_change, max_dir_change, var_dir_change, msg_id_diff_sum, non_integer_diffs_fraction]
#
# def load_model(model_path, scaler_path):
#     model = joblib.load(model_path)
#     scaler = joblib.load(scaler_path)
#     return model, scaler
#
#
# def classify_data(data, model, scaler):
#     features = extract_features(data)
#     features_scaled = scaler.transform([features])
#     return model.predict(features_scaled)
#
#
# def main():
#     model_path = './model/trained_model-sort-notall.joblib'
#     scaler_path = './model/scaler-sort-notall.joblib'
#     model, scaler = load_model(model_path, scaler_path)
#     data_path = './test/traceJSON-2217-2215-A0-18472-0.json'
#     data_buffer = {}
#     window_size = 4
#     step_size = 1
#
#     with open(data_path, 'r') as file:
#         for line in file:
#             data = json.loads(line)
#             sender_pseudo = data['senderPseudo']
#
#             if sender_pseudo not in data_buffer:
#                 data_buffer[sender_pseudo] = []
#
#             data_buffer[sender_pseudo].append(data)
#
#             # Check if the buffer has enough data to start the sliding window process
#             if len(data_buffer[sender_pseudo]) >= window_size:
#                 for start in range(len(data_buffer[sender_pseudo]) - window_size + 1):
#                     window = data_buffer[sender_pseudo][start:start + window_size]
#                     label = classify_data(window, model, scaler)
#                     print(f"Data batch with senderPseudo {sender_pseudo} classified as {label}")
#
#                 # Move the window by one step
#                 data_buffer[sender_pseudo] = data_buffer[sender_pseudo][step_size:]
#
# if __name__ == "__main__":
#     main()

# import json
# import numpy as np
# from sklearn.preprocessing import StandardScaler
# from sklearn.ensemble import RandomForestClassifier
# import joblib
#
# def calculate_direction_change(hed_x, hed_y):
#     changes = []
#     for i in range(1, len(hed_x)):
#         dot_product = np.dot([hed_x[i - 1], hed_y[i - 1]], [hed_x[i], hed_y[i]])
#         norms_product = np.linalg.norm([hed_x[i - 1], hed_y[i - 1]]) * np.linalg.norm([hed_x[i], hed_y[i]])
#         dot_product = max(min(dot_product / norms_product, 1), -1)
#         change = np.arccos(dot_product)
#         changes.append(np.degrees(change))
#     return changes if changes else [0]
#
# def extract_features(data):
#     send_times = [d['sendTime'] for d in data]
#     send_time_diffs = [send_times[i] - send_times[i - 1] for i in range(1, len(send_times))]
#     non_integer_diffs_fraction = np.mean([not np.isclose(diff, round(diff), atol=2e-4) for diff in send_time_diffs])
#     acl_x, acl_y, hed_x, hed_y, spd, msg_ids = zip(
#         *[(d['acl'][0], d['acl'][1], d['hed'][0], d['hed'][1], np.linalg.norm(d['spd']), d['messageID']) for d in data])
#     dir_changes = calculate_direction_change(hed_x, hed_y)
#     mean_dir_change = np.mean(dir_changes) if dir_changes else 0
#     max_dir_change = np.max(dir_changes) if dir_changes else 0
#     var_dir_change = np.var(dir_changes) if dir_changes else 0
#     pos_ratio_x = np.sum(np.array(acl_x) > 0) / (np.sum(np.array(acl_x) < 0) + 1e-5)
#     pos_ratio_y = np.sum(np.array(acl_y) > 0) / (np.sum(np.array(acl_y) < 0) + 1e-5)
#     dispersion = np.var(acl_x) + np.var(acl_y)
#     var_x = np.var(acl_x)
#     var_y = np.var(acl_y)
#     mean_acl_x = np.mean(acl_x)
#     mean_acl_y = np.mean(acl_y)
#     mean_spd = np.mean(spd)
#     var_spd = np.var(spd)
#     msg_id_diff_sum = np.sum(np.diff(msg_ids))
#     #print([pos_ratio_x, pos_ratio_y, dispersion, var_x, var_y, mean_acl_x, mean_acl_y, mean_spd, var_spd,mean_dir_change, max_dir_change, var_dir_change, msg_id_diff_sum, non_integer_diffs_fraction])
#     features = np.array([pos_ratio_x, pos_ratio_y, dispersion, var_x, var_y, mean_acl_x, mean_acl_y, mean_spd, var_spd,
#                          mean_dir_change, max_dir_change, var_dir_change]) #, msg_id_diff_sum]) #, non_integer_diffs_fraction])
#     return features.reshape(1, -1)  # 将一维数组转换为二维数组
#     #return features
#
# def load_model(model_path):
#     return joblib.load(model_path)
#
# def classify_data(data, model):
#     features = extract_features(data)
#
#     return model.predict(features)[0]
#
# def main():
#     model_path = './model/trained_model-without-s-sort-notall.joblib'
#     model = load_model(model_path)
#     data_path = './test/traceJSON-10935-10933-A16-25365-0.json'
#     data_buffer = {}
#     window_size = 5
#     step_size = 1
#
#     with open(data_path, 'r') as file:
#         for line in file:
#             data = json.loads(line)
#             sender_pseudo = data['senderPseudo']
#
#             if sender_pseudo not in data_buffer:
#                 data_buffer[sender_pseudo] = []
#
#             data_buffer[sender_pseudo].append(data)
#
#             if len(data_buffer[sender_pseudo]) >= window_size:
#                 for start in range(0, len(data_buffer[sender_pseudo]) - window_size + 1, step_size):
#                     window = data_buffer[sender_pseudo][start:start + window_size]
#                     label = classify_data(window, model)
#                     print(f"Data batch with senderPseudo {sender_pseudo} classified as {label}")
#
#                 data_buffer[sender_pseudo] = data_buffer[sender_pseudo][step_size:]
#
# if __name__ == "__main__":
#     main()



import json
import numpy as np
from sklearn.preprocessing import StandardScaler
from sklearn.ensemble import RandomForestClassifier
import joblib

def calculate_direction_change(hed_x, hed_y):
    changes = []
    for i in range(1, len(hed_x)):
        dot_product = np.dot([hed_x[i - 1], hed_y[i - 1]], [hed_x[i], hed_y[i]])
        norms_product = np.linalg.norm([hed_x[i - 1], hed_y[i - 1]]) * np.linalg.norm([hed_x[i], hed_y[i]])
        dot_product = max(min(dot_product / norms_product, 1), -1)
        change = np.arccos(dot_product)
        changes.append(np.degrees(change))
    return changes if changes else [0]

def extract_features(data):
    send_times = [d['sendTime'] for d in data]
    send_time_diffs = [send_times[i] - send_times[i - 1] for i in range(1, len(send_times))]
    non_integer_diffs_fraction = np.mean([not np.isclose(diff, round(diff), atol=2e-4) for diff in send_time_diffs])
    acl_x, acl_y, hed_x, hed_y, spd, msg_ids = zip(
        *[(d['acl'][0], d['acl'][1], d['hed'][0], d['hed'][1], np.linalg.norm(d['spd']), d['messageID']) for d in data])
    dir_changes = calculate_direction_change(hed_x, hed_y)
    mean_dir_change = np.mean(dir_changes) if dir_changes else 0
    max_dir_change = np.max(dir_changes) if dir_changes else 0
    var_dir_change = np.var(dir_changes) if dir_changes else 0
    pos_ratio_x = np.sum(np.array(acl_x) > 0) / (np.sum(np.array(acl_x) < 0) + 1e-5)
    pos_ratio_y = np.sum(np.array(acl_y) > 0) / (np.sum(np.array(acl_y) < 0) + 1e-5)
    dispersion = np.var(acl_x) + np.var(acl_y)
    var_x = np.var(acl_x)
    var_y = np.var(acl_y)
    mean_acl_x = np.mean(acl_x)
    mean_acl_y = np.mean(acl_y)
    mean_spd = np.mean(spd)
    var_spd = np.var(spd)
    msg_id_diff_sum = np.sum(np.diff(msg_ids))
    #print([pos_ratio_x, pos_ratio_y, dispersion, var_x, var_y, mean_acl_x, mean_acl_y, mean_spd, var_spd,mean_dir_change, max_dir_change, var_dir_change, msg_id_diff_sum, non_integer_diffs_fraction])
    features = np.array([pos_ratio_x, pos_ratio_y, dispersion, var_x, var_y, mean_acl_x, mean_acl_y, mean_spd, var_spd,
                         mean_dir_change, max_dir_change, var_dir_change]) #, msg_id_diff_sum]) #, non_integer_diffs_fraction])
    return features.reshape(1, -1)  # 将一维数组转换为二维数组
    #return features


def load_model(model_path):
    return joblib.load(model_path)

def classify_data(data, model):
    features = extract_features(data)
    return model.predict(features)[0]

def main():
    model_path = './model/trained_model-without-s-sort-all-5.joblib'
    model = load_model(model_path)
    data_path = './test/1.json'
    data_buffer = {}
    window_size = 5
    step_size = 1

    with open(data_path, 'r') as file, open('result.txt', 'w') as result_file:
        for line in file:
            data = json.loads(line)
            sender_pseudo = data['senderPseudo']

            if sender_pseudo not in data_buffer:
                data_buffer[sender_pseudo] = []

            data_buffer[sender_pseudo].append(data)

            if len(data_buffer[sender_pseudo]) >= window_size:
                for start in range(0, len(data_buffer[sender_pseudo]) - window_size + 1, step_size):
                    window = data_buffer[sender_pseudo][start:start + window_size]
                    label = classify_data(window, model)
                    result = f"{sender_pseudo} {label}"
                    print(result)
                    result_file.write(result + '\n')

                data_buffer[sender_pseudo] = data_buffer[sender_pseudo][step_size:]

if __name__ == "__main__":
    main()
